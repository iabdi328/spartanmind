/**
 * @file ids.h
 * @author Ismail Abdi
 *
 *
 */
 
#ifndef IDS_H
#define IDS_H

// Enum to define custom IDs for levels and other menu items
enum IDs {
 // Level IDs - used for loading different levels
    IDM_LEVEL1 = wxID_HIGHEST + 1,
    IDM_LEVEL2 = wxID_HIGHEST + 2,
    IDM_LEVEL3 = wxID_HIGHEST + 3,

 // Standard Menu Item IDs
 IDM_EXIT,          // ID for the "Exit" menu item
 IDM_ABOUT          // ID for the "About" menu item
};

#endif //IDS_H
