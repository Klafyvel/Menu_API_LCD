#ifndef H_MENU
#define H_MENU

#include "Arduino.h"
#include "LiquidCrystal.h"

#include <string.h>

#include "Listuino/Listuino/Listuino.h"

#define MAX_LABEL_LONG 20

#define MENU_QUIT -1

typedef void (*callback)(void);
class Menu;

typedef struct Item
{
    bool is_submenu;
    union {
        Menu* submenu;
        callback function;
    } content;
    char label[MAX_LABEL_LONG];
} Item;

class Menu
{
public:
    Menu(char title[], LiquidCrystal* lcd, \
         uint8_t pb_up, uint8_t pb_down, uint8_t pb_ok);
    ~Menu();
    bool addSubMenu(Menu* submenu, const char name[]);
    bool addItem(callback function, const char name[]);
    void removeItemByLabel(const char name[]);
    void removeItemById(int id);
    bool action(int action);
    int choose();
    void print(uint8_t current);

private:
    List <Item*> _items;
    int _last_item;
    char _title[MAX_LABEL_LONG];
    LiquidCrystal* _lcd;
    uint8_t _pb_up;
    uint8_t _pb_down;
    uint8_t _pb_ok;
};
#endif