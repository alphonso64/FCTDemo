#ifndef CONST_DEFINE_H
#define CONST_DEFINE_H

//#define LAYER_1_KERNEL "D:\\test1\\"

#define CAM_CAP 100
#define CAM2_CAP 1000
#define PIC_CAP 101
#define CALI_CAP 102

#define SUCCESS 0
#define FAIL -1

//#define USBCHECK
#define USB_CHECK_MAX_CNT 3

#define LOCALTEST

#ifdef LOCALTEST
#define LAYER_1_KERNEL "D:\\test1\\conv_layer1_kernel.txt"
#define LAYER_2_KERNEL "D:\\test1\\conv_layer2_kernel.txt"
#define LAYER_3_KERNEL "D:\\test1\\conv_layer3_kernel.txt"
#define LAYER_1_BIAS "D:\\test1\\conv_layer1_bias.txt"
#define LAYER_2_BIAS "D:\\test1\\conv_layer2_bias.txt"
#define LAYER_3_BIAS "D:\\test1\\conv_layer3_bias.txt"
#define TEMPSPATH "D:\\test1\\temps"
#define PATTERN_FILE_PATH "C:\\Users\\alphonso\\Desktop\\code.ini"
#else
#define LAYER_1_KERNEL "./bin/conv_layer1_kernel.txt"
#define LAYER_2_KERNEL "./bin/conv_layer2_kernel.txt"
#define LAYER_3_KERNEL "./bin/conv_layer3_kernel.txt"
#define LAYER_1_BIAS "./bin/conv_layer1_bias.txt"
#define LAYER_2_BIAS "./bin/conv_layer2_bias.txt"
#define LAYER_3_BIAS "./bin/conv_layer3_bias.txt"
#define TEMPSPATH "./temps"
#define PATTERN_FILE_PATH "./bin/code.ini"
#endif


#endif // CONST_DEFINE_H
