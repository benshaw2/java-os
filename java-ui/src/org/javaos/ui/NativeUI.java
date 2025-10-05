// java-ui/src/org/javaos/ui/NativeUI.java

package org.javaos.ui;

public class NativeUI {

    static {
        String arch = System.getProperty("os.arch");
        String libName = "ui_native";

        if (!arch.equals("aarch64") && !arch.equals("x86_64") && !arch.equals("amd64")) {
            throw new UnsupportedOperationException("Unsupported architecture: " + arch);
        }

        try {
            System.loadLibrary(libName);
            System.out.println("Loaded native library: " + libName);
        } catch (UnsatisfiedLinkError e) {
            System.err.println("Failed to load native library: " + e.getMessage());
            throw e;
        }
    }

    public static native boolean init();
    public static native void clear(int color);
    public static native void drawRect(int x, int y, int w, int h, int color);
    public static native void shutdown();
}

