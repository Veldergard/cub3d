/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaurine <olaurine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 20:30:47 by olaurine          #+#    #+#             */
/*   Updated: 2020/10/08 20:58:09 by olaurine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void cub_drayw_walls(t_g *g)
{
	int		r;
	int		mx;
	int		my;
	int		dof;
	int		lineH;
	int		lineO;
	float	ca;
	float	vx;
	float	vy;
	float	rx;
	float	ry;
	float	ray;
	float	xo;
	float	yo;
	float	disV;
	float	disH;
	float	Tan;
	float	step;

	r = 0;
	ray = g->player.dir - 30 * DR;
	ray = ray < 0 ? ray + 2 * PI : ray;
	ray = ray > 2 * PI ? ray - 2 * PI : ray;
	step = 60. * DR / (float)g->win.x;
	while (r < g->win.x)
	{
		dof = 0;
		disV = 100000;
		Tan = tan(ray);
		if (cos(ray) > 0.001)
		{
			rx = (((int)g->player.x >> 6) << 6) + 64;
			ry = (g->player.x - rx) * Tan + g->player.y;
			xo = 64;
			yo = -xo * Tan;
		}
		else if (cos(ray) < -0.001)
		{
			rx = (((int)g->player.x >> 6) << 6) - 0.0001;
			ry = (g->player.x - rx) * Tan + g->player.y;
			xo = -64;
			yo = -xo * Tan;
		}
		else
		{
			rx = g->player.x;
			ry = g->player.y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			if(mx >= 0 && my >= 0 && mx < g->map.x && my < g->map.y &&
				g->map.tab[my][mx] == '1')
			{
				dof = 8;
				disV = cos(ray) * (rx - g->player.x) - sin(ray) * (ry - g->player.y);
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		vx = rx;
		vy = ry;

		dof = 0;
		disH = 100000;
		Tan = 1.0 / Tan;
		if (sin(ray) > 0.001)
		{
			ry = (((int)g->player.y >> 6) << 6) - 0.0001;
			rx = (g->player.y - ry) * Tan + g->player.x;
			yo = -64;
			xo = -yo * Tan;
		}
		else if (sin(ray) < -0.001)
		{
			ry = (((int)g->player.y >> 6) << 6) + 64;
			rx = (g->player.y - ry) * Tan + g->player.x;
			yo = 64;
			xo = -yo * Tan;
		}
		else
		{
			rx = g->player.x;
			ry = g->player.y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			if (mx >= 0 && my >= 0 && mx < g->map.x && my < g->map.y &&
				g->map.tab[my][mx] == '1')
			{
				dof = 8;
				disH = cos(ray) * (rx - g->player.x) - sin(ray) * (ry - g->player.y);
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		if (disV < disH)
			disH = disV;
		ca = g->player.dir - ray;
		disH = disH * cos(ca);
		lineH = (CUB_SIZE * g->win.y) / disH;
		lineH = lineH > g->win.y ? g->win.y : lineH;
		lineO = (int)(g->win.y - lineH) / 2;
		cub_draw_line(g, r, lineO, lineH + lineO);
		// ray -= ray - 1 * DR;
		ray += step;
		ray = ray < 0 ? ray + 2 * PI : ray;
		ray = ray > 2 * PI ? ray - 2 * PI : ray;
		r++;
	}
}

  double posX = 22, posY = 12;  //x and y start position
  double dirX = -1, dirY = 0; //initial direction vector
  double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

  double time = 0; //time of current frame
  double oldTime = 0; //time of previous frame

  screen(screenWidth, screenHeight, 0, "Raycaster");
  while(!done())
  {
    for(int x = 0; x < w; x++)
    {
      //calculate ray position and direction
      double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
      double rayDirX = dirX + planeX * cameraX;
      double rayDirY = dirY + planeY * cameraX;
      //which box of the map we're in
      int mapX = int(posX);
      int mapY = int(posY);

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

       //length of ray from one x or y-side to next x or y-side
      double deltaDistX = std::abs(1 / rayDirX);
      double deltaDistY = std::abs(1 / rayDirY);
      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?
      //calculate step and initial sideDist
      if(rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
      }
      if(rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
      }
      //perform DDA
      while (hit == 0)
      {
        //jump to next map square, OR in x-direction, OR in y-direction
        if(sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        if(worldMap[mapX][mapY] > 0) hit = 1;
      }
      //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
      if(side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
      else          perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

      //Calculate height of line to draw on screen
      int lineHeight = (int)(h / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + h / 2;
      if(drawStart < 0)drawStart = 0;
      int drawEnd = lineHeight / 2 + h / 2;
      if(drawEnd >= h)drawEnd = h - 1;

      //choose wall color
      ColorRGB color;
      switch(worldMap[mapX][mapY])
      {
        case 1:  color = RGB_Red;    break; //red
        case 2:  color = RGB_Green;  break; //green
        case 3:  color = RGB_Blue;   break; //blue
        case 4:  color = RGB_White;  break; //white
        default: color = RGB_Yellow; break; //yellow
      }

      //give x and y sides different brightness
      if(side == 1) {color = color / 2;}

      //draw the pixels of the stripe as a vertical line
      verLine(x, drawStart, drawEnd, color);
    }
