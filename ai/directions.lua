function authorized_entities(point)
	if (point == "." or
		point == "B" or
		type(point) == "number") then
		return 1
	end
	return 0
end

function check_directions(map, cur_x, cur_y, i_x, i_y)
	local move = 0
	local nb = nil

	for i = 1, (AGGRO * 2) + 1 do
		if (nb ~= nil and authorized_entities(map[cur_y][cur_x])) then
			if (nb + 1 > AGGRO and map[cur_y][cur_x] ~= nb - 1) then
				return move
			end
			if ((type(map[cur_y][cur_x]) == "number" and
				(nb + 1 < tonumber(map[cur_y][cur_x]))) or
				(map[cur_y][cur_x] == "." or map[cur_y][cur_x] == "B"))
			then
				map[cur_y][cur_x] = nb + 1
				move = move + 1
			end
		end
		nb = tonumber(map[cur_y][cur_x])
		cur_x, cur_y = cur_x + i_x, cur_y + i_y
		if (cur_y == 0 or cur_y == MAP_YMAX + 1 or
			cur_x == 0 or cur_x == MAP_XMAX + 1)
		then return move end
	end
	return move
end

function init_direction(map, n1, n2, i_x, i_y, d_x, d_y)
	local cur_x, cur_y = n1, n2
	local move = 0

	for i = 1, AGGRO * 2 do
		move = move + check_directions(map, cur_x, cur_y, i_x, i_y)
		cur_x, cur_y = cur_x + d_x, cur_y + d_y
		if (cur_x == MAP_XMAX + 1 or
			cur_y == MAP_YMAX + 1)
		then break end
	end
	return move
end

function go_all_directions(map, cur_x, cur_y)
	local n1 = cur_x - AGGRO

	if (n1 <= 0) then n1 = 1 end
	local n2 = cur_x + AGGRO
	if (n2 > MAP_XMAX) then n2 = MAP_XMAX end
	local n3 = cur_y - AGGRO
	if (n3 <= 0) then n3 = 1 end
	local n4 = cur_y + AGGRO
	if (n4 > MAP_YMAX) then n4 = MAP_YMAX end
	local move = 0
	move = move + init_direction(map, n1, n4, 0, -1, 1, 0)	-- up
	move = move + init_direction(map, n1, n3, 0, 1, 1, 0)	-- down
	move = move + init_direction(map, n1, n3, 1, 0, 0, 1)	-- right
	move = move + init_direction(map, n2, n3, -1, 0, 0, 1)	-- left
	if (move ~= 0) then
		return 1
	end
	return 0
end
