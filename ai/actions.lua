function go_out_danger(map, x, y, nb)
	if (map[y][x] == ".") then
		X_TMP, Y_TMP = x, y
	end
	if (nb < BOMB_RANGE + 1) then
		if (y + 1 < MAP_YMAX and map[y + 1][x] ~= "W" and map[y + 1][x] ~= "B") then
			go_out_danger(map, x, y + 1, ++nb)
		elseif (y - 1 > 0 and map[y - 1][x] ~= "W" and map[y - 1][x] ~= "B") then
			go_out_danger(map, x, y - 1, ++nb)
		elseif (x + 1 < MAP_YMAX and map[y][x + 1] ~= "W" and map[y][x + 1] ~= "B") then
			go_out_danger(map, x + 1, y, ++nb)
		elseif (x - 1 > 0 and map[y][x - 1] ~= "W" and map[y][x - 1] ~= "B") then
			go_out_danger(map, x - 1, y, ++nb)
		end
	end
end

function random_movement()
	local mov = {1, -1, 1, -1}
	local n = math.random(1, 4)

	if (n == 1 or n == 2) then
		local x = X + mov[n]
		if (x < 1) then x = 1 end
		if (x > MAP_XMAX) then x = MAP_XMAX end
	else
		local y = Y + mov[n]
		if (y < 1) then y = 1 end
		if (y > MAP_YMAX) then y = MAP_YMAX end
	end
	return x, y
end
