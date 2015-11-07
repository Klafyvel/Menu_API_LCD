#include "menu.h"

Menu::Menu(char title[], LiquidCrystal* lcd, uint8_t pb_up, uint8_t pb_down, uint8_t pb_ok)
{
    _lcd = lcd;
    _lcd->noBlink();
    _lcd->noCursor();
    _pb_ok = pb_ok;
    _pb_up = pb_up;
    _pb_down = pb_down;
    _last_item = 0;

    if(strlen(title) <= MAX_LABEL_LONG){strcpy(_title, title);}
}

bool Menu::addItem(callback function, const char name[])
{
    Item* item = new Item;
    if (item == NULL || strlen(name)>=MAX_LABEL_LONG)
        return false;
    item->is_submenu = false;
    item->content.function = function;
    strcpy(item->label, name);
    
    _items.append(item);

    return true;
}
bool Menu::addSubMenu(Menu* submenu, const char name[])
{
    Item* item = new Item;
    if (item == NULL || strlen(name)>=MAX_LABEL_LONG)
        return false;
    item->is_submenu = true;
    item->content.submenu = submenu;
    strcpy(item->label, name);

    _items.append(item);

    return true;
}

void Menu::removeItemByLabel(const char name[])
{
    int index = 0;
    for(ListElement<Item*>* i = _items.get(0); i != 0; i=i->getNext()){
        if (!strcmp(i->getValue()->label, name))
            _items.removeValue(index);
        index ++;
    }
}

void Menu::removeItemById(int id) 
{
    _items.removeValue(id);
}

Menu::~Menu() 
{
    _items.~List();
}
void Menu::print(uint8_t current)
{
    _lcd->clear();
    _lcd->print(_title);
    _lcd->print(" :");

    _lcd->setCursor(0,1);

    if (current <= _items.getLength()) {
        Item* item = _items.getValue(current);
        _lcd->print(item->label);
    }
    else
        _lcd->print("Exit");
}

int Menu::choose() 
{
    int choice = _last_item;
    bool running = true;
    int length = _items.getLength();

    while(running)
    {
        Menu::print(choice);
        bool event = false;
        while(!event) {
            if(digitalRead(_pb_down)==LOW) { choice ++;event = true;}
            if(digitalRead(_pb_up)==LOW) { choice --;event = true;}
            if(digitalRead(_pb_ok)==LOW) { event = true;running = false;}
            choice = (choice)%(length+1);
        }
        delay(200);
    }
    if(choice==length) 
    {
        _last_item = 0;
        return MENU_QUIT;
    }
    else
    {
        _last_item = choice;
        return choice;
    }
}

bool Menu::action(int action)
{
    if((action<0)||(action >= _items.getLength()))
        return false;

    callback function;

    Item* item = _items.getValue(action);
    bool r = true;
    if(item->is_submenu)
    {
        int a;
        do {
            a = item->content.submenu->choose();
            r = item->content.submenu->action(a);
        } while(r);
    }
    else
        item->content.function();

    return r;
}