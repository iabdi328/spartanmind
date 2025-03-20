/**
 * @file PopUps.cpp
 * @author Emmanuel Koshy
 */
 
#include "pch.h"
#include "PopUps.h"
#include <wx/font.h>
#include <wx/pen.h>
#include <wx/brush.h>
#include <wx/graphics.h>
#include <algorithm>
#include <sstream>

void PopUps::ShowPopup(const std::wstring& message, double duration)
{
    mMessage = message;
    mDuration = duration;
    mElapsed = 0.0;
    mVisible = true;
}

void PopUps::Update(double elapsed)
{
    if (!mVisible) return;

    mElapsed += elapsed;
    if (mElapsed >= mDuration)
    {
        // Hide the popup after time is up
        mVisible = false;
    }
}

void PopUps::Draw(std::shared_ptr<wxGraphicsContext> gc, int width, int height)
{
    if (!mVisible || !gc) return;

    // MSU green
    wxColour customColor(24, 69, 59);

    // The pop-up box dimensions
    double boxWidth = 600;
    double boxHeight = 300;
    double x = (width - boxWidth) / 2.0;
    double y = (height - boxHeight) / 2.0;

    // Outline & fill
    wxPen pen(*wxBLACK, 2);
    wxBrush brush(*wxWHITE);
    gc->SetPen(pen);
    gc->SetBrush(brush);
    gc->DrawRectangle(x, y, boxWidth, boxHeight);

    //
    // 1) Title sizing (same logic as before)
    //
    double horizontalMargin = 10.0;
    double maxAllowedWidth = boxWidth - 2.0 * horizontalMargin;
    wxString levelTitle = mMessage; // e.g., "Level 2 Begins!"
    int titleFontSize = 72;  // start large
    wxFont titleFont(wxFontInfo(titleFontSize).FaceName("Arial").Bold());
    gc->SetFont(titleFont, customColor);

    double twTitle, thTitle;
    gc->GetTextExtent(levelTitle, &twTitle, &thTitle);

    // Keep shrinking until we fit horizontally
    while (twTitle > maxAllowedWidth && titleFontSize > 10)
    {
        titleFontSize -= 2;
        wxFont smallerFont(wxFontInfo(titleFontSize).FaceName("Arial").Bold());
        gc->SetFont(smallerFont, customColor);
        gc->GetTextExtent(levelTitle, &twTitle, &thTitle);
    }

    // Place near the top with a small vertical margin
    double marginTop = 20.0;
    double textXTitle = x + (boxWidth - twTitle) / 2.0;
    double textYTitle = y + marginTop;
    gc->DrawText(levelTitle, textXTitle, textYTitle);

    //
    // 2) Instructions block
    //
    wxString instructions =
        L"Spacebar: Grab\n"
        L"A-Z or - : Release\n"
        L"Shift: Headbutt";

    // Start instructions at a bigger size, e.g. 40
    int instructionsFontSize = 40;
    wxFont instructionsFont(wxFontInfo(instructionsFontSize).FaceName("Arial"));
    gc->SetFont(instructionsFont, *wxBLACK);

    // Parse instructions into lines
    std::wistringstream iss((std::wstring)instructions);
    std::vector<wxString> lines;
    {
        std::wstring line;
        while(std::getline(iss, line))
        {
            lines.push_back(line);
        }
    }

    // We'll measure the total block height
    double lineSpacing = 2.0; // smaller spacing between lines
    double totalHeight = 0.0;
    std::vector<std::pair<double,double>> lineExtents; // store (w,h) for each line

    for(auto &l : lines)
    {
        double lw, lh;
        gc->GetTextExtent(l, &lw, &lh);
        lineExtents.push_back({lw, lh});
        totalHeight += lh + lineSpacing;
    }
    if(!lines.empty()) totalHeight -= lineSpacing; // remove extra spacing after last line

    // The gap between the title and the first instruction line is only 10px now
    double instructionsStartY = textYTitle + thTitle + 10.0;

    // If totalHeight doesn't fit from instructionsStartY down to the bottom
    // we can do a shrinking loop like before:
    double bottomMargin = 20.0;
    double availableSpace = (y + boxHeight) - instructionsStartY - bottomMargin;

    while ((totalHeight > availableSpace) && (instructionsFontSize > 10))
    {
        instructionsFontSize -= 2;
        wxFont smallerInstFont(wxFontInfo(instructionsFontSize).FaceName("Arial"));
        gc->SetFont(smallerInstFont, *wxBLACK);

        // recalc totalHeight
        totalHeight = 0.0;
        lineExtents.clear();
        for(auto &l : lines)
        {
            double lw, lh;
            gc->GetTextExtent(l, &lw, &lh);
            lineExtents.push_back({lw, lh});
            totalHeight += lh + lineSpacing;
        }
        if(!lines.empty()) totalHeight -= lineSpacing;

        availableSpace = (y + boxHeight) - instructionsStartY - bottomMargin;
    }

    // Place each instruction line starting at instructionsStartY
    gc->SetFont(wxFont(wxFontInfo(instructionsFontSize).FaceName("Arial")), *wxBLACK);
    double currentY = instructionsStartY;
    for(size_t i=0; i<lines.size(); i++)
    {
        double lw = lineExtents[i].first;
        double lh = lineExtents[i].second;
        double lineX = x + (boxWidth - lw)/2.0;
        gc->DrawText(lines[i], lineX, currentY);
        currentY += lh + lineSpacing;
    }
}
