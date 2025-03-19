/**
 * @file LoadLevel.cpp
 * @author Raj Ambekar
 */

#include "pch.h"
#include "LoadLevel.h"
#include "Declaration.h"
#include "DeclarationPlayer.h"
#include "Item.h"
#include "ItemPlayer.h"
#include <string>
#include <sstream>

LoadLevel::LoadLevel()
{

}

void LoadLevel::LoadFromXML(const wxString &filename)
{
    wxXmlDocument xmlDoc;
    /*
    if (!xmlDoc.Load(filename))
    {
        return;
    }
    */

    bool test = xmlDoc.Load(filename);

    auto root = xmlDoc.GetRoot();


    mWidth = wxAtoi(root->GetAttribute("width"));
    mHeight = wxAtoi(root->GetAttribute("height"));
    mTileWidth = wxAtoi(root->GetAttribute("tilewidth"));
    mTileHeight = wxAtoi(root->GetAttribute("tileheight"));

    auto node = root->GetChildren();
    for (auto current = node; current != nullptr; current->GetNext())
    {
        wxString nodeType = current->GetName();
        if (nodeType == L"declarations")
        {
            auto declarationNode = node->GetChildren();
            LoadXmlDeclaration(declarationNode);
        }
        else if (nodeType == L"game")
        {
            mWordCol = wxAtoi(current->GetAttribute("col"));
            mWordRow = wxAtoi(current->GetAttribute("row"));
            mWordLength = wxAtoi(current->GetAttribute("length"));
            std::stringstream ss(current->GetNodeContent().ToStdString());
            int number;
            while (ss >> number)
            {
                mWord.push_back(number);
            }

        }
        else if (nodeType == L"items")
        {
            auto itemNode = node->GetChildren();
            LoadXmlItem(itemNode);
        }

    }

}

void LoadLevel::LoadXmlDeclaration(wxXmlNode *node)
{
    std::shared_ptr<Declaration> declaration;
    wxString type = node->GetName();
    if (type == L"player")
    {
        declaration = std::make_shared<DeclarationPlayer>(this);
    }

    if (declaration != nullptr)
    {
        declaration->XmlLoad(node);
        mDeclarations.push_back(declaration);
    }
}

void LoadLevel::LoadXmlItem(wxXmlNode *node)
{
    std::shared_ptr<Item> item;
    wxString type = node->GetName();
    wxString id = node->GetAttribute(L"id");
    if (type == L"player")
    {
        item = std::make_shared<ItemPlayer>(this);
    }

    if (item != nullptr)
    {
        item->XmlLoad(node);
        mItems.push_back(item);
    }
}
void LoadLevel::OnDraw(std::shared_ptr<wxGraphicsContext> graphics)
{
    for (auto item : mItems)
    {
        item->Draw(graphics);
    }
}
