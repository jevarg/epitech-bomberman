function go_out_danger(map, x, y, nb)
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
