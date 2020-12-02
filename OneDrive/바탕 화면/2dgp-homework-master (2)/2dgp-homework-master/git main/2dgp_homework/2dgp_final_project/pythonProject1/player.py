import random
from pico2d import *
import gfw
from gobj import *
from bullet import *
bullet_x = 0
bullet_y = 0
spark_x = 0
spark_y = 0
class Player:
    KEY_XMAP = {
        (SDL_KEYDOWN, SDLK_LEFT):  -1,
        (SDL_KEYDOWN, SDLK_RIGHT):  1,
        (SDL_KEYUP, SDLK_LEFT):     1,
        (SDL_KEYUP, SDLK_RIGHT):   -1,
    }
    KEY_YMAP = {
        (SDL_KEYDOWN, SDLK_UP): 1,
        (SDL_KEYDOWN, SDLK_DOWN): -1,
        (SDL_KEYUP, SDLK_UP): -1,
        (SDL_KEYUP, SDLK_DOWN): 1,
    }
    KEYDOWN_SPACE = (SDL_KEYDOWN, SDLK_SPACE)
    LASER_INTERVAL = 0.15
    SPARK_INTERVAL = 0.08
    IMAGE_RECTS = [
        (  3, 0, 42, 65),
        ( 45, 0, 42, 65),
        (87, 0, 42, 65),
        (129, 0, 42, 65),
        (171, 0, 42, 65),
        (213, 0, 42, 65),
        (255, 0, 42, 65),
    ]
    MAX_ROLL = 0.4
    SPARK_OFFSET = 28
    spark_position_downer = -100
    Life = 10
    #constructor
    def __init__(self):
        # self.pos = get_canvas_width() // 2, get_canvas_height() // 2
        self.x, self.y = 250, 80
        self.dx = 0
        self.dy = 0
        self.speed = 320
        self.image = gfw.image.load(RES_DIR + '/plane1 (1).png')
        self.spark = gfw.image.load(RES_DIR + '/Arcade - Strikers 1945 3 Strikers 1999 - F-117 Bomb (1).png')
        self.src_rect = Player.IMAGE_RECTS[5]
        half_x = 1.5+self.src_rect[2] // 2
        half_y = self.src_rect[3]//2
        self.minx = half_x
        self.miny = half_y
        self.maxx = get_canvas_width() - half_x
        self.maxy = get_canvas_height() - half_y
        self.bullet_sound = load_wav(RES_DIR + '/bullet_sound.wav')
        self.bullet_sound.set_volume(64)

        self.laser_time = 0
        self.roll_time = 0
        self.bgm = load_music(RES_DIR+'/mainstate_bgm.mp3')
        self.bgm.set_volume(48)
        self.bgm.repeat_play()
    def fire(self):
        self.laser_time = 0
        bullet = LaserBullet(self.x, self.y + Player.SPARK_OFFSET, 400)
        self.bullet_sound.play()
        gfw.world.add(gfw.layer.bullet, bullet)
        # print('bullets = ', len(LaserBullet.bullets))
        #총쏘는거 clip_draw썼음.

    def draw(self):
        self.image.clip_draw(*self.src_rect, self.x, self.y)
        #if self.laser_time < Player.SPARK_INTERVAL:
             #self.spark.clip_draw(spark_x, spark_y, 150,243,self.x, self.y + Player.SPARK_OFFSET+Player.spark_position_downer)
        #비행기 그리는거.src.rect는 l,b,w,h 튜플

    def update(self):
        if self.Is_alive():
            self.x += self.dx * self.speed * gfw.delta_time
            self.y+=self.dy*self.speed*gfw.delta_time
            self.laser_time += gfw.delta_time
            self.x = clamp(self.minx, self.x, self.maxx)
            self.y = clamp(self.miny, self.y, self.maxy)
            self.update_roll()
        # if self.laser_time >= Player.LASER_INTERVAL:
        #     self.fire()

    def update_roll(self):
        dx = self.dx
        dy = self.dy
        if dx == 0:
            if self.roll_time > 0:
                dx = -1
            elif self.roll_time < 0:
                dx = 1

        self.roll_time += dx * gfw.delta_time
        if self.dx == 0:
            if dx < 0 and self.roll_time < 0:
                self.roll_time = 0
            if dx > 0 and self.roll_time > 0:
                self.roll_time = 0

        self.roll_time = clamp(-Player.MAX_ROLL, self.roll_time, Player.MAX_ROLL)

        # if self.roll_time
        roll = int(self.roll_time * 3 / Player.MAX_ROLL)
        self.src_rect = Player.IMAGE_RECTS[roll + 3]

        # if self.src_rect != self.prev_rect:
        #     print(roll, self.src_rect)
        #     self.prev_rect = self.src_rect
    def Is_alive(self):
        if self.Life <=0:
            return False
        return True
    def collision_checker(self):#충돌체크

        pass
    def handle_event(self, e):
        pair = (e.type, e.key)
        if pair in Player.KEY_XMAP:
            self.dx += Player.KEY_XMAP[pair]
        elif pair in Player.KEY_YMAP:
            self.dy += Player.KEY_YMAP[pair]
        if e.type==SDL_KEYDOWN and e.key ==SDLK_SPACE:
            self.fire()

    def get_bb(self):
        hw = self.src_rect[2] / 2
        hh = self.src_rect[3] / 2
        return self.x - hw, self.y - hh, self.x + hw, self.y + hh

if __name__ == "__main__":
    for (l,t,r,b) in Player.IMAGE_RECTS:
        l *= 2
        t *= 2
        r *= 2
        b *= 2
        l -= 1
        r += 2
        print('(%3d, %d, %d, %d),' % (l,t,r,b))