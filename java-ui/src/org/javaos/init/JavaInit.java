package org.javaos.init;

import org.javaos.ui.NativeUI;

public class JavaInit {
    public static void main(String[] args) {
        System.out.println("[JavaInit] Starting init process...");

        try {
            System.out.println("[JavaInit] Mounting /proc...");
            Runtime.getRuntime().exec("mount -t proc proc /proc");

            System.out.println("[JavaInit] Mounting /sys...");
            Runtime.getRuntime().exec("mount -t sysfs sys /sys");

            System.out.println("[JavaInit] Mounting /dev...");
            Runtime.getRuntime().exec("mount -t devtmpfs dev /dev");

            Thread.sleep(1000); // Give mounts time to settle

            System.out.println("[JavaInit] Initializing framebuffer...");
            if (NativeUI.init()) {
                System.out.println("[JavaInit] Framebuffer initialized successfully.");
                NativeUI.clear(0x000000); // Clear to black
                NativeUI.drawRect(50, 50, 100, 100, 0x00FF00); // Draw green square
                System.out.println("[JavaInit] UI rendered.");
            } else {
                System.err.println("[JavaInit] Failed to initialize framebuffer.");
            }

            System.out.println("[JavaInit] Entering idle loop...");
            while (true) {
                Thread.sleep(1000);
            }

        } catch (Exception e) {
            System.err.println("[JavaInit] Exception occurred: " + e.getMessage());
            e.printStackTrace();
        }
    }
}