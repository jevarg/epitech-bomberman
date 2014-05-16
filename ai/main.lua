dofile("ai/global.lua")
dofile("ai/utils.lua")
dofile("ai/best_first.lua")

function check_bomb(map)
	return true
end

function check_character(map)
	return true
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
		if (entities[i]["type"] == 6) then
			map[entities[i]["y"]][entities[i]["x"]] = "W"
		elseif (entities[i]["type"] == 7) then
			map[entities[i]["y"]][entities[i]["x"]] = "."
		elseif (entities[i]["type"] == 1) then
			map[entities[i]["y"]][entities[i]["x"]] = "P"
		elseif (entities[i]["type"] == 4) then
			map[entities[i]["y"]][entities[i]["x"]] = "B"
		end
	end
	return map
end

function artificial_intelligence()
	local ent = {}
	local entities = {}
	local translate = {
		[0] = TYPE_PRIORITY["wall"],
		[1] = TYPE_PRIORITY["box"],
		[2] = TYPE_PRIORITY["free"],
		[4] = TYPE_PRIORITY["player"]
	}

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
	local map = create_map(entities, arg["aggro"])
	display_map(map)
	if (check_bomb(map) and check_character(map)) then
		return best_first(map, entities)
	end
end

X, Y = arg["x"], arg["y"]
AGGRO = arg["aggro"]
MAP_XMAX = AGGRO
MAP_YMAX = AGGRO
return artificial_intelligence()
