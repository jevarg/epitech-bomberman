dofile("ai/global.lua")
dofile("ai/utils.lua")
dofile("ai/danger_dir.lua")
dofile("ai/construct_map.lua")
dofile("ai/actions.lua")
dofile("ai/shortest_priority.lua")

function launch_passive()
	local entities = get_entities()
	local map = create_map(entities, AGGRO)
	local cur_x, cur_y = random_movement(fill_dangerous_fields(map))
	return determine_way(map, cur_x, cur_y)
end

X, Y = arg["x"], arg["y"]
AGGRO = arg["aggro"]
launch_passive()