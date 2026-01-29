import sensor
import time
import ustruct
from pyb import UART

# 摄像头初始化
sensor.reset()
sensor.set_pixformat(sensor.GRAYSCALE)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time=2000)
clock = time.clock()

# 曝光和增益设置
sensor.set_auto_exposure(False, exposure_us=40000)
sensor.set_auto_gain(False, gain_db=10)
sensor.skip_frames(time=2000)

# 图像中心点
CENTER_X = 160
CENTER_Y = 120

# 串口初始化 - P4(RX), P5(TX)
uart = UART(3, 115200, timeout=1000)

def send_target_data(cx, cy):
    """
    发送目标坐标数据到STM32
    数据格式: 帧头(2字节) + X坐标(2字节) + Y坐标(2字节) + 校验和(1字节) + 帧尾(1字节)
    """
    # 计算偏差 (-160 到 +160)
    dx = int(cx - CENTER_X)
    dy = int(cy - CENTER_Y)
    
    # 数据打包: 帧头0xAA55 + dx + dy + 校验和 + 帧尾0xFF
    checksum = (dx + dy) & 0xFF
    data_pack = ustruct.pack('<HHHBB', 0xAA55, dx & 0xFFFF, dy & 0xFFFF, checksum, 0xFF)
    
    uart.write(data_pack)
    print("发送数据: dx=%d, dy=%d" % (dx, dy))

def send_no_target():
    """发送无目标信号"""
    data_pack = ustruct.pack('<HHHBB', 0xAA55, 0x8000, 0x8000, 0x00, 0xFF)
    uart.write(data_pack)
    print("无目标")

while True:
    clock.tick()
    img = sensor.snapshot().binary([(0,160)])
    
    # 寻找最大矩形
    rect = None
    rect_max_mag = 0
    for r in img.find_rects(threshold=10000):
        if r.w() < 30 or r.h() < 30:
            continue
        if r.magnitude() < rect_max_mag:
            continue
        rect = r
        rect_max_mag = r.magnitude()
    
    if rect:
        # 计算矩形中心点
        cx = rect.x() + rect.w()/2
        cy = rect.y() + rect.h()/2
        
        # 发送目标坐标
        send_target_data(cx, cy)
        
        # 绘制矩形和中心点
        img.draw_rectangle(rect.rect(), color=(255, 0, 0))
        img.draw_circle(int(cx), int(cy), 5, color=(0, 255, 0))
        
    else:
        # 发送无目标信号
        send_no_target()
    
    time.sleep_ms(50)  # 控制发送频率
    print("FPS %f" % clock.fps())