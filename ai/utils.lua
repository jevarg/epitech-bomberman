function display_map(map)
	for i = 1, #map do
		for k, v in pairs(map[i]) do
			io.write(map[i][k])
			nb = tonumber(map[i][k])
			if (nb ~= nil) then
				if (nb > 9) then
					io.write("  ")
				else
					io.write("   ")
				end
			else
				io.write("   ")
			end
		end
		io.write("\n")
	end
end

function get_entities()
	local translate = {
		[0] = TYPE_PRIORITY["wall"],
		[1] = TYPE_PRIORITY["box"],
		[2] = TYPE_PRIORITY["free"],
		[4] = TYPE_PRIORITY["player"]
	}
	local ent = {}
	local entities = {}
	for i = 1, #arg, 3 do
		table.insert(ent, {["type"] = translate[arg[i]], ["y"] = arg[i + 1], ["x"] = arg[i + 2]})
	end
	for i = 1, 8 do
		for j = 1, #ent do
			if (ent[j]["type"] == i) then
				table.insert(entities, ent[j])
			end
		end
	end
	return entities	
end

function create_map(entities, aggro)
	local map = {}

	for i = 1, aggro do
		table.insert(map, {})
		for j = 1, aggro do
			table.insert(map[i], " ")
		end
	end
	for i = 1, #entities do
		if (entities[i]["type"] == TYPE_PRIORITY["wall"]) then
			map[entities[i]["y"]][entities[i]["x"]] = "W" end
		if (entities[i]["type"] == TYPE_PRIORITY["free"]) then
			map[entities[i]["y"]][entities[i]["x"]] = "." end
		if (entities[i]["type"] == TYPE_PRIORITY["player"]) then
			map[entities[i]["y"]][entities[i]["x"]] = "P" end
		if (entities[i]["type"] == TYPE_PRIORITY["box"]) then
			map[entities[i]["y"]][entities[i]["x"]] = "B" end
		if (entities[i]["type"] == TYPE_PRIORITY["bomb"]) then
			map[entities[i]["y"]][entities[i]["x"]] = "O" end
	end
	return map
end

function set_priority(level)
	if (level == 1) then
		local player, item, box, bomb, wall, free = 1, 2, 3, 4, 5, 6
	elseif (level == 2) then
		local player, item, box, bomb, wall, free = 1, 2, 3, 4, 5, 6
	elseif (level == 3) then
		local player, item, box, bomb, wall, free = 1, 2, 3, 4, 5, 6
	end
	TYPE_PRIORITY = {
		["player"] = player,
		["item"] = item,
		["box"] = box,
		["bomb"] = bomb,
		["wall"] = wall,
		["free"] = free
	}
end
