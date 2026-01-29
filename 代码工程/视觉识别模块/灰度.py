import sensor, image, time,pyb
from pyb import UART

uart = UART(3, 115200)
uart.init(115200, bits=8, parity=None, stop=1)

# 初始化摄像头
sensor.reset()
sensor.set_pixformat(sensor.GRAYSCALE)  # 设置为灰度模式
sensor.set_framesize(sensor.QVGA)       # 分辨率320x240
sensor.skip_frames(time=2000)           # 等待摄像头稳定
# sensor.set_vflip(True)
# sensor.set_hmirror(True)
LED1=pyb.LED(1)#pyb是模块，led是其中一个类
LED2=pyb.LED(2)
LED3=pyb.LED(3)
LED1.on()
LED2.on()
LED3.on()
BLACK_THRESHOLD = (0, 80)  # 可调

# 定义色块检测参数
MIN_PIXELS = 100     # 最小像素数（过滤噪声）
MAX_PIXELS = 23500   # 最大像素数（过滤大面积区域）
AREA_THRESHOLD = 50  # 区域面积阈值（可选）
clock = time.clock()
max_density=0.2
max_solidity=0.5
max_convexity=0.6
min_area=1600
max_area=23500#可调
def line_intersection(line1, line2):
    """
    计算两条直线的交点坐标
    """
    (x1, y1, x2, y2) = line1
    (x3, y3,x4, y4) = line2

    # 计算分母（判断是否平行）
    den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)
    if den == 0:
        # 分母为0，两直线平行或重合，无唯一交点
        return (abs(x2-x1)//2,abs(y2-y1)//2)

    # 计算分子
    t_num = (x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)
    s_num = (x1 - x3) * (y1 - y2) - (y1 - y3) * (x1 - x2)

    t = t_num / den
    s = s_num / den

    # 计算交点坐标
    x = x1 + t * (x2 - x1)
    y = y1 + t * (y2 - y1)

    return (x, y)
flag=0
target_x_2=0
target_y_2=0
ccx=0
ccy=0#这四个变量是让识别不到时也保证发送上一次识别到的变量
while True:
    img = sensor.snapshot()         # 捕获一帧图像
    clock.tick()
    valid_blobs = []
    flag=1

    # 查找符合阈值的色块
    blobs = img.find_blobs([BLACK_THRESHOLD],
                          pixels_threshold=MIN_PIXELS,
                          area_threshold=AREA_THRESHOLD,
                          x_stride=1,
                          y_stride=1,
                          margin=15,
                          )  # 合并相邻色块

    if blobs:

        for blob in blobs:

            if blob.density()<max_density:

                if blob.area()>min_area and blob.area()<max_area:

                    #print(blob.density(),blob.solidity(),blob.convexity())
                    img.draw_rectangle(blob.rect(), color=(255,0,0))
                    #print(blob.density(),blob.solidity(),blob.convexity())
                    ##0.152698 0.167296 0.423312
                    # valid_blobs.append(blob)
                    if blob.solidity()<max_solidity:
                        if blob.convexity()<max_convexity:
                            valid_blobs.append(blob)


    if valid_blobs:
            min_density_blob = min(valid_blobs, key=lambda b: b.density())
            img.draw_line(min_density_blob.major_axis_line())
            img.draw_line(min_density_blob.minor_axis_line())
            intersection=line_intersection(min_density_blob.major_axis_line(), min_density_blob.minor_axis_line())

            lx1=abs(min_density_blob.major_axis_line()[0]-min_density_blob.major_axis_line()[2])
            ly1=abs(min_density_blob.major_axis_line()[1]-min_density_blob.major_axis_line()[3])
            l1=lx1**2+ly1**2
            l1=l1**(1/2)
            lx2=abs(min_density_blob.minor_axis_line()[0]-min_density_blob.minor_axis_line()[2])
            ly2=abs(min_density_blob.minor_axis_line()[1]-min_density_blob.minor_axis_line()[3])
            l2=lx2**2+ly2**2
            l2=l2**(1/2)
            #print(l2/l1)

            if l2/l1>0.7:#可调
                #img.draw_rectangle(min_density_blob.rect(), color=(255,0,0))
                img.draw_cross(min_density_blob.min_corners()[0][0], min_density_blob.min_corners()[0][1])
                img.draw_cross(min_density_blob.min_corners()[1][0], min_density_blob.min_corners()[1][1])
                img.draw_cross(min_density_blob.min_corners()[2][0], min_density_blob.min_corners()[2][1])
                img.draw_cross(min_density_blob.min_corners()[3][0], min_density_blob.min_corners()[3][1])
                #img.draw_cross(int(min_density_blob.cxf()), int(min_density_blob.cyf()), color=(255,0,255))
                img.draw_circle(min_density_blob.enclosing_circle(),color=(255,255,0), thickness=2, fill=False)
                img.draw_cross(int(intersection[0]),int(intersection[1]), color=(255,0,0))
                target_x=170
                target_y=104
                target_x_2=1
                target_y_2=1
                img.draw_cross(target_x,target_y, color=(0,0,0))
                print(intersection)#靶心坐标
                ccx=int(intersection[0])
                ccy=240-int(intersection[1])
                #串口发送示例
                data = bytearray([0x55,target_x,240-target_y,int(intersection[0]),240-int(intersection[1]) & 0xFF])
                print(0x55,target_x,240-target_y,int(intersection[0]),240-int(intersection[1]))
                uart.write(data)
            else:
                if flag==1:
                    if ccx:
                        if ccy:
                            if target_x_2:
                                if target_y_2:
                                    #串口发送示例
                                    data = bytearray([0x55,0,0,0,0 ])
                                    uart.write(data)
    else:
        if flag==1:
            if ccx:
                if ccy:
                    if target_x_2:
                        if target_y_2:
                            #串口发送示例
                            data = bytearray([0x55,0,0,0,0])
                            uart.write(data)







    print(clock.fps())

