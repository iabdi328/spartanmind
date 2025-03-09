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
 IDM_LOAD_LEVEL0 = wxID_HIGHEST + 1,  // Start custom IDs from the highest wxWidgets ID
 IDM_LOAD_LEVEL1,
 IDM_LOAD_LEVEL2,
 IDM_LOAD_LEVEL3,

 // Standard Menu Item IDs
 IDM_EXIT,          // ID for the "Exit" menu item
 IDM_ABOUT          // ID for the "About" menu item
};

#endif //IDS_H
