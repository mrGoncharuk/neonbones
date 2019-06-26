/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vehicle_moving.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 20:24:40 by mhonchar          #+#    #+#             */
/*   Updated: 2019/06/26 21:48:50 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "neon.h"



float			ft_vec2_len(t_vector2 v)
{
	return (sqrt((v.x * v.x) + (v.y * v.y)));
}

void			ft_init_vehicle(t_vehicle *moto)
{
	moto->acc_power = 0.00005;
	moto->lateral_friction_factor = 0.0005;
	moto->backward_friction_factor = 0.0005;
	moto->acc_input = 0;
	moto->max_speed = (t_vector2){2, 2};
	moto->vel_vec = (t_vector2){0.005, 0};
	moto->acc_vec = (t_vector2){0, 0};
}


t_vector2		ft_normaliza_vec2(t_vector2 v)
{
	t_vector2	norm;
	float		len;

	len = ft_vec2_len(v);
	norm.x = v.x / len;
	norm.y = v.y / len;
	return (norm);
}

void			ft_ride(t_game *game, t_vehicle *moto, int dt)
{
	t_player	*player;
	t_vector2	curr_speed;
	t_vector2	lateral_vel_vec;
	t_vector2	lateral_frict_vec;
	 t_vector2	right_vec;
	t_vector2	backwards_frict_vec;

	right_vec.x = 1;
	right_vec.y = 0;
	player = &(game->player);
	moto->acc_vec.x = 1 * moto->acc_input * moto->acc_power;
	moto->acc_vec.y = 1 * moto->acc_input * moto->acc_power;
	lateral_vel_vec.x = right_vec.x * (moto->vel_vec.x * right_vec.x);
	lateral_vel_vec.y = 0;
	lateral_frict_vec.x = -lateral_vel_vec.x * moto->lateral_friction_factor;
	lateral_frict_vec.y = 0;
	backwards_frict_vec.x = -moto->vel_vec.x * moto->backward_friction_factor;
	backwards_frict_vec.y = -moto->vel_vec.y * moto->backward_friction_factor;

	moto->vel_vec.x += (backwards_frict_vec.x + lateral_frict_vec.x) * dt;
	moto->vel_vec.y += (backwards_frict_vec.y + lateral_frict_vec.y) * dt;
	curr_speed = ft_normaliza_vec2(moto->vel_vec);
	printf("curr_speed x =[%f], y = [%f]\n", curr_speed.x, curr_speed.y);
	printf("player_x [%f] player_y[%f]\n", player->pos.x, player->pos.y);
	if (ft_vec2_len(curr_speed) < ft_vec2_len(moto->max_speed))
	{
		printf("true");
		moto->vel_vec.x += moto->acc_vec.x * dt;
		moto->vel_vec.y += moto->acc_vec.y * dt;
	}
	printf("acc_input [%f], x =[%f], y = [%f], dt =[%d]\n", moto->acc_input, moto->vel_vec.x, moto->vel_vec.y, dt);
	player->pos.x += moto->vel_vec.x * dt;
	player->pos.y += moto->vel_vec.y * dt;
}