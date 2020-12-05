import random
import gfw
from pico2d import *
from enemy import Enemy

delta_time = 0
GEN_X = [ 50, 150, 250, 350, 450 ]
WAVE_TYPE = [ 1, 2, 3, 4]
PLANE_WAVE_TYPE = [
    [
     [25, 75],
     [100, 150],
     [175, 225],
     [475, 425],
     [400, 375],
     [350, 325],
    ],#왼쪽 2번씩 3번, 오른쪽 2번씩 3번
    [
     [75, 150],
     [350, 425],
     [225, 325],
     [150, 200, 250, 300, 350],
     [25, 75, 125, 375, 425, 475]
    ],#왼, 오른, 가운데, 중앙굵게, 중앙만 뺴고
    [
     [25],
     [50],
     [75],
     [100],
     [125],
     [150],
     [175],
     [200],
     [225],
     [250],
     [275],
     [300],
     [325],
     [350],
     [375],
     [400],
     [425],
     [450],
     [475],
    ],#왼쪽부터 25간격으로 오른쪽 끝까지
    [
     [100, 200, 300, 400],
     [50, 150, 250, 350, 450],
     [50, 450],
     [100, 400],
     [150, 350],
     [200, 300],
     [250],
     [200, 300],
     [150, 350],
     [100, 400],
     [50, 450],
    ],#사이로 2번, 좁혀지기1번, 넓혀지기1번
    ]#4가지 종류
GATE_WAVE_TYPE = [
    [
    [100],
    [400],
    [250],
    [200],
    [300]
    ],#좌 우 중 중좌 중우
    [
     [100, 200],
     [300, 400]
    ],#좌 둘 우 둘
    [
     [50, 150, 250],
     [250, 350, 450],
     [200, 300]
    ]#좌 삼 우 삼 중 둘
]#3가지 종류
WHEEL_WAVE_TYPE = [
    [
        [450, 50],
        [400, 100],
        [350, 150]
    ],#양 끝부터 좁히며 3번
    [
        [50, 100, 150, 200, 250, 300, 350, 400, 450]
    ]#맵 전체로
]# 2가지 종류
next_wave = 0
wave_index = 0

def update():
    global next_wave
    next_wave -= gfw.delta_time
    if next_wave < 0:
        generate_wave()
    global delta_time
    delta_time = gfw.delta_time

def generate_wave():
    global wave_index, next_wave
    for x in GEN_X:
        level = enemy_level()
        speed = -(100 + 5 * wave_index)
        e = Enemy(x, speed, level)
        gfw.world.add(gfw.layer.enemy, e)

    wave_index = random.uniform(0,9)
    next_wave = random.uniform(3, 4)#wave변화 속도

LEVEL_ADJUST_PERCENTS = [ 10, 15, 15, 40, 15, 5 ] # -3 ~ 2
def enemy_level():
    level = (wave_index - 5) // 10 - 3;
    percent = random.randrange(100)
    pl = level
    pp = percent
    for p in LEVEL_ADJUST_PERCENTS:
        if percent < p: break
        percent -= p
        level += 1
    # print(pl, '->', level, ', ', pp, '->', percent)
    if level < 1: level = 1
    if level > 20: level = 20
    return level
