
command.turn = 0
command.throttle = 1
temp = status.collision
if status.collision > 0:
    command.turn = 0
