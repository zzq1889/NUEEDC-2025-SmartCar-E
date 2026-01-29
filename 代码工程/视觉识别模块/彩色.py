import sensor, image, time, pyb, math
from pyb import UART

uart = UART(3, 115200)
uart.init(115200, bits=8, parity=None, stop=1)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)

sensor.skip_frames(time=1000)
sensor.set_auto_gain(True)
sensor.set_auto_whitebal(True)
# sensor.set_vflip(True)
#sensor.set_hmirror(True)

LED1=pyb.LED(1)#pyb是模块，led是其中一个类
LED2=pyb.LED(2)
LED3=pyb.LED(3)
LED1.on()
LED2.on()
LED3.on()
clock = time.clock()
threshold_blackblob=[(0, 29, -24, 6, -5, 16)]
min_area=1600
max_area=21500#这个可调
max_density=0.2
max_solidity=0.5
max_convexity=0.6

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
while(True):
    valid_blobs = []
    clock.tick()
    ##先串口接收
    if uart.any():
        pt = uart.readchar()
        pt = chr(pt)
        print(pt)
        # pt=uart.readline().decode()
        # print(pt)
    ##拍照
    img = sensor.snapshot()
    blobs = img.find_blobs(threshold_blackblob,pixels_threshold=1, area_threshold=1,x_stride=1,y_stride=1,margin=15)
    if blobs:
        valid_blobs = []
        for blob in blobs:
            if blob.density()<max_density:
                if blob.area()>min_area and blob.area()<max_area:#这个可调（max_area）
                    if blob.w()>blob.h():#这个可调
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
            if l2/l1>0.7:#这个可调
                #img.draw_rectangle(min_density_blob.rect(), color=(255,0,0))  # 红色矩形框
                img.draw_cross(min_density_blob.min_corners()[0][0], min_density_blob.min_corners()[0][1])
                img.draw_cross(min_density_blob.min_corners()[1][0], min_density_blob.min_corners()[1][1])
                img.draw_cross(min_density_blob.min_corners()[2][0], min_density_blob.min_corners()[2][1])
                img.draw_cross(min_density_blob.min_corners()[3][0], min_density_blob.min_corners()[3][1])
                #img.draw_cross(int(min_density_blob.cxf()), int(min_density_blob.cyf()), color=(255,0,255))
                img.draw_circle(min_density_blob.enclosing_circle(),color=(0,0,0), thickness=2, fill=False)
                img.draw_cross(int(intersection[0]),int(intersection[1]), color=(255,0,0))

                target_x=184
                target_y=105
                img.draw_cross(target_x,target_y, color=(0,0,0))
                #print(intersection)#靶心坐标
                #串口发送示例
                data = bytearray([0x55,target_x,240-target_y,int(intersection[0]),240-int(intersection[1]) & 0xFF])
                uart.write(data)
                print(intersection)#靶心坐标

    print(clock.fps())


