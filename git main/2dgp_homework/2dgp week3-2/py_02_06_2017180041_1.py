import helper
from pico2d import *
global running
speed =10
goal = True
x=0
y=85
pos = x,y

#main
open_canvas()

gra = pico2d.load_image('../res/grass.png')
cha = load_image('../res/animation_sheet.png')
frame_index = 0
action = 0
running = True
dxdy = 0,0
left_right = True
move_on = False
next_purpose = [(None, None)]
click_count = 0
pos_stack_cnt = 0
ddxy = 0,0
start_move = False

while running:
    clear_canvas() 
    
    events = get_events()
    frame_index = (frame_index+1)%8
    gra.draw(400,30) 
    
    if goal:
        if next_purpose[pos_stack_cnt] is (None, None):
            if next_purpose[pos_stack_cnt]==pos:
                ++pos_stack_cnt
                print(pos_stack_cnt)
        speed=-3
        if pos_stack_cnt==click_count:
            for i in (0,click_count):
                next_purpose[i] = None, None
            pos_stack_cnt, click_count = (0,0)
            start_move = False
        else:
            move_on = True
        if left_right:
            cha.clip_draw(100 * frame_index,200,100,100,pos[0],pos[1])#_left_stay
        else:
            cha.clip_draw(100 * frame_index,300,100,100,pos[0],pos[1])#_right_stay
    else:
        pos, goal = helper.move_toward(pos, dxdy, next_purpose[pos_stack_cnt])
        if left_right:
            cha.clip_draw(100 * frame_index,0,100,100,pos[0],pos[1])#left
        else:
            cha.clip_draw(100 * frame_index,100,100,100,pos[0],pos[1])#right
            print(pos_stack_cnt)
    frame_index = (frame_index+1)%8
    for event in events:
        if  (event.type == SDL_KEYDOWN and event.key == SDLK_ESCAPE) or \
            (event.type==SDL_MOUSEBUTTONDOWN and event.button==SDL_BUTTON_LEFT and\
            event.key == SDL_QUIT):
            running = False        
        if event.type == SDL_MOUSEBUTTONDOWN and event.button == SDL_BUTTON_RIGHT:
            start_move = True
            ++click_count
            Mx, My = event.x, 600-event.y-1
            if goal:
                goal = False
                move_on =True
                speed = 10
                next_purpose = [(Mx, My)]
            else:
                speed+=3
                next_purpose+=[(Mx, My)]
            ##next_purpose += [(x,y)]
            if next_purpose[pos_stack_cnt][0]>pos[0]:
                left_right = False
            else:
                left_right = True
    if move_on:
        if next_purpose[pos_stack_cnt] != (None, None):
            dxdy = helper.delta(pos, next_purpose[pos_stack_cnt], speed)   
    else:
        pass
    #cha.clip_draw(100 * frame_index,200,100,100,x,85)#left_stay
    #cha.clip_draw(100 * frame_index,0,100,100,x,85) #left
    delay(0.05)
    update_canvas()
    
close_canvas()
