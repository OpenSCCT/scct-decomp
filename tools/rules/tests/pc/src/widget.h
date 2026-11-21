/* no-game-data: synthetic */
#ifndef WIDGET_H
#define WIDGET_H

#define WIDGET_HIDDEN	0x00000001	/* widget->flags */

typedef struct widget_s {
	int		flags;
	float	scale;
	struct widget_s	*next;
} widget_t;

extern int	g_widgetCount;

/* widget.c */
int Widget_Count( void );
void Widget_Hide( widget_t *widget );

#endif /* WIDGET_H */
