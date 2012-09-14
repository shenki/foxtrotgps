#ifndef __ROUTE_H
#define __ROUTE_H

/**
 * Clear the route.
 */
void
reset_route ();

/**
 * This function draws the current route on the screen.
 */
void
paint_route ();

/** 
 * Find the bounding box of the given GSList containin waypoints.
 */
bbox_t
get_way_bbox (GSList *ways);

/**
 * Append a new waypoint at the end of the route.
 */
void 
append_waypoint_to_route (double lat, double lon);

/**
 * Delete the given waypoint from the route.
 */
void 
delete_waypoint_of_route (waypoint_t *wp);

/**
 * Find the route waypoint which wp_icon is at the given mouse position.
 * Return that waypoint or NULL if none was found.
 */
waypoint_t *
find_routepoint (int mouse_x, int mouse_y);

/**
 * Change the position of the given waypoint to the new position.
 */
void
change_waypoint_of_route (waypoint_t *wp, double lat, double lon);

/**
 * Insert a new waypoint before the given waypoint. This waypoint lies
 * between the given waypoint and the waypoint before this waypoint.
 */
void
insert_waypoint_before_of_route (waypoint_t *wp);

/**
 * Save the route in GPX format to the given URI.
 */
void
save_route_as_gpx (const char *uri);

/**
 * Save a route to a TomTom ITN file format.
 */
void
save_route_as_tomtom_itn (const char *uri);

/**
 * Load a route from a given GPX file.
 */
void
load_route (const char *filename);

char *
choose_save_file (char *currentName);

char *
choose_load_file ();

#endif
