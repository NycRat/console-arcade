#pragma once

int MENU_processInput(int (*f1)(), int (*f2)(), int (*f3)());
int MENU_executeOption(int (*f1)(), int (*f2)(), int (*f3)());
void MENU_initialize(char *o1, char *o2, char *o3);
void MENU_render();
