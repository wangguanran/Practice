#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/leds.h>

// LED设备结构体
struct demo_led_data {
	struct led_classdev cdev;
};

// 全局变量
static struct demo_led_data demo_led;

// LED亮度设置函数
static void demo_led_brightness_set(struct led_classdev *cdev,
				    enum led_brightness brightness)
{
	pr_info("demo_led: set brightness to %d\n", brightness);
}

// LED初始化函数
static int __init demo_led_init(void)
{
	int ret;

	pr_info("demo_led: initializing\n");

	// 初始化LED类设备
	demo_led.cdev.name = "demo_led";
	demo_led.cdev.brightness_set = demo_led_brightness_set;
	demo_led.cdev.max_brightness = LED_FULL;

	// 注册LED类设备
	ret = led_classdev_register(NULL, &demo_led.cdev);
	if (ret < 0) {
		pr_err("demo_led: failed to register LED device\n");
		return ret;
	}

	pr_info("demo_led: initialized successfully\n");
	return 0;
}

// LED退出函数
static void __exit demo_led_exit(void)
{
	pr_info("demo_led: exiting\n");

	// 注销LED类设备
	led_classdev_unregister(&demo_led.cdev);

	pr_info("demo_led: exited successfully\n");
}

module_init(demo_led_init);
module_exit(demo_led_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Demo LED driver");
