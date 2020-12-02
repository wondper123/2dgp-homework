from pico2d import *

open_canvas()

gra = load_image('res/grass.png')
cha = load_image('res/character.png')

x=0
while x<800:
    clear_canvas() #
    gra.draw(400,30) #
    cha.draw(x,85) #rendering
    update_canvas()

    get_events()
    
    x+=2
    
    delay(0.01)
close_canvas()

#game loop
# - update() - logic *
# - event-handling
# - draw() - rendering *
