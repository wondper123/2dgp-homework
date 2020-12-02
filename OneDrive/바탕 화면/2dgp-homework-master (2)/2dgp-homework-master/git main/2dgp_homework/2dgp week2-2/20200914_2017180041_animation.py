from pico2d import *

open_canvas()

gra = pico2d.load_image('res/grass.png')
cha = load_image('res/animation_sheet.png')

x=0
frame_index = 0
action = 0
while x<800:
    clear_canvas() #
    gra.draw(400,30) #
    cha.clip_draw(100 * frame_index,action * 100,100,100,x,85) #rendering
    update_canvas()

    evts = get_events()
    
    x+=2
    if x%100 == 0:
        action = (action+1) % 4
    # logic
    #frame_index+=1
    #if frame_index>=8:
       # frame_index=0

    frame_index = (frame_index+1)%8
    
    delay(0.01)
close_canvas()

#game loop
# - update() - logic *
# - event-handling
# - draw() - rendering *
