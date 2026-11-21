/* no-game-data: synthetic */
/* widget.c -- a unit that passes every rule */

#include "widget.h"

int	g_widgetCount;

/*
================
Widget_Count
================
*/
int Widget_Count( void ) {
	return g_widgetCount;
}

/*
================
Widget_Hide

Hides the widget and every widget linked after it.
================
*/
void Widget_Hide( widget_t *widget ) {
	while ( widget ) {
		widget->flags |= WIDGET_HIDDEN;
		widget = widget->next;
	}
}
