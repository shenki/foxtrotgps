

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib/gprintf.h>

#define TILESIZE 256


float
deg2rad(float deg)
{
	return (deg * M_PI / 180);
}

float
rad2deg(float rad)
{
	return (rad / M_PI * 180);
}


int
lat2pixel(	float zoom,
		float lat)
{
	float lat_m;
	int pixel_y;

	lat_m = atanh(sin(lat));
	
	
	
	pixel_y = -( (lat_m * TILESIZE * exp(zoom * M_LN2) ) / (2*M_PI)) + 
		    (exp(zoom * M_LN2) * (TILESIZE/2) );


	return pixel_y;
}


int
lon2pixel(	float zoom,
		float lon)
{
	int pixel_x;

	pixel_x = ( (lon * TILESIZE * exp(zoom * M_LN2) ) / (2*M_PI) ) + 
		    ( exp(zoom * M_LN2) * (TILESIZE/2) );
	return pixel_x;
}

float
pixel2lon(	float zoom,
		int pixel_x)
{
	float lon;
	
	lon = ((pixel_x - ( exp(zoom * M_LN2) * (TILESIZE/2) ) ) *2*M_PI) / 
			(TILESIZE * exp(zoom * M_LN2) );
	
	return lon;
}

float
pixel2lat(	float zoom,
		int pixel_y)
{
	float lat, lat_m;

	lat_m = (-( pixel_y - ( exp(zoom * M_LN2) * (TILESIZE/2) ) ) * (2*M_PI)) /
				(TILESIZE * exp(zoom * M_LN2));
	
	lat = asin(tanh(lat_m));
	
	printf("lat %f => lat_m %f \n", lat,lat_m);
	
	
	return lat;
}

char *
latdeg2latmin(	float lat)
{
	static char latmin[20];
	int degrees;
	float minutes;
	
	degrees = abs( (lat>0) ? floor(lat) : ceil(lat) );
	minutes = (fabs(lat) - (float)degrees) * 60;
	
	g_sprintf(	latmin,
			"%d°%.3f' %s", 
			degrees,
			minutes,
			(lat>0) ? "N" : "S");
	
	return latmin;
}

char *
londeg2lonmin(	float lon)
{
	static char lonmin[20];
	int degrees;
	float minutes;
	
	degrees = abs( (lon>0) ? floor(lon) : ceil(lon) );
	minutes = (fabs(lon) - (float)degrees) * 60;
	
	g_sprintf(	lonmin,
			"%d°%.3f' %s",
			degrees,
			minutes,
			(lon>0) ? "E" : "W");
	
	return lonmin;
}

char *
latdeg2latsec(	float lat)
{
	static char latsec[20];
	int degrees, full_minutes;
	float minutes, seconds;
	
	degrees = abs( (lat>0) ? floor(lat) : ceil(lat) );
	minutes = (fabs(lat) - (float)degrees) * 60;
	full_minutes = floor(minutes);
	seconds = (minutes - (float)full_minutes) * 60;
	
	g_sprintf(	latsec,
			"%d°%d'%.2f\" %s", 
			degrees,
			full_minutes,
			seconds,
			(lat>0) ? "N" : "S");
	
	return latsec;
}

char *
londeg2lonsec(	float lon)
{
	static char lonmin[20];
	int degrees, full_minutes;
	float minutes, seconds;
	
	degrees = abs( (lon>0) ? floor(lon) : ceil(lon) );
	minutes = (fabs(lon) - (float)degrees) * 60;
	full_minutes = floor(minutes);
	seconds = (minutes - (float)full_minutes) * 60;
	
	g_sprintf(	lonmin,
			"%d°%d'%.2f\" %s",
			degrees,
			full_minutes,
			seconds,
			(lon>0) ? "E" : "W");
	
	return lonmin;
}


float
get_bearing(double lat1, double lon1, double lat2, double lon2)
{
	double bearing, tmp, tmp2;

	tmp = atan2(sin(lon2-lon1) * cos(lat2),
		    cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos(lon2-lon1) );

	tmp2 = tmp;
	
	bearing = (tmp2<0) ? tmp2+M_PI*2 : tmp2;

        

	return bearing;
}

float
get_distance(double lat1, double lon1, double lat2, double lon2)
{
	float distance = 0;
	double tmp;
	
	tmp = sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(lon2 - lon1);
	
	distance = 6371.0 *  acos(tmp);

	printf("DISTANCE: acos(%.2f), ll1: %f, %f -- ll2: %f, %f\n", tmp, lat1, lon1, lat2, lon2);
	
	return distance;
}

int
get_zoom_covering(int width, int height, double lat_max, double lon_min, double lat_min, double lon_max)
{
	int pixel_x1, pixel_y1, pixel_x2, pixel_y2;
	float zoom = 17.0;

	while (zoom>=2)
	{
		
		pixel_x1 = lon2pixel((float)zoom, deg2rad(lon_min));
		pixel_y1 = lat2pixel((float)zoom, deg2rad(lat_max));
		
		pixel_x2 = lon2pixel((float)zoom, deg2rad(lon_max));
		pixel_y2 = lat2pixel((float)zoom, deg2rad(lat_min));
		
		
		if( 	(pixel_x1+width)  > pixel_x2	&&
			(pixel_y1+height) > pixel_y2 )
		{
			return zoom;
		}
		zoom--;
	}	
	
	return zoom;
}
