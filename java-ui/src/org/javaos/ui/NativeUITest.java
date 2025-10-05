// java-ui/src/org/javaos/ui/NativeUITest.java

package org.javaos.ui;

public class NativeUITest {
    public static void main(String[] args) {
        System.out.println("Architecture: " + System.getProperty("os.arch"));

        if (NativeUI.init()) {
            System.out.println("Framebuffer initialized.");

            NativeUI.clear(0x000000); // Clear to black
            NativeUI.drawRect(50, 50, 100, 100, 0xFF0000); // Draw red square
            System.out.println("Rectangle drawn.");

            NativeUI.shutdown();
            System.out.println("Framebuffer shutdown.");
        } else {
            System.err.println("Failed to initialize framebuffer.");
        }
    }
}
