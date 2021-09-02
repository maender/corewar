# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    jeanmichaelvincent.s                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/11 11:53:41 by maabou-h          #+#    #+#              #
#    Updated: 2019/08/11 16:46:30 by edjubert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.name		"Jean Michael Vincent"
.comment	"We need a Jean Michael Vincent in register r1"

init:		live %0
			st	r1, -4

protecc:	st r1, r2
			st r1, r3
			ld -18, r7
			ld -19, r8
			ld -20, r9
			fork %:init
			and r5, r4, r5

spread:		live %0
			st r7, -500
			st r8, -501
			st r9, -502
			fork %:init
