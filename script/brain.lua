command.throttle = 1.0;
print(status.x);
if status.collision == COLLISION.WALL then
    command.turn = 1.0;
end