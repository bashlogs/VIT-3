import java.awt.*;
import javax.swing.*;
import java.applet.*;
import java.util.*;

public class Unipolar extends JFrame {
    String bin;

    public Unipolar(String b) {
        this.bin = b;
        setSize(800, 800);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }

    public void paint(Graphics g) {
        super.paint(g);
        g.setColor(Color.BLACK);
        g.drawLine(75, 75, 75, 750);
        g.drawLine(75, 750, 750, 750);
        g.setColor(Color.RED);
        int x1 = 75, x0 = 75, y1 = 675, y0 = 750;
        // Draw '0' and '1' labels on the y-axis
        g.drawString("0", 50, 755);
        g.drawString("1", 50, 675);
        for (int i = 0; i < bin.length(); i++) {
            if (i == 0) {
                if (bin.charAt(i) == '1') {
                    g.drawLine(x1, y1, x1 + 75, y1);
                    g.drawString("1", x1 + 30, y1 - 10);
                    x1 += 75;
                    x0 += 75;
                } else {
                    g.drawLine(x0, y0, x0 + 75, y0);
                    g.drawString("0", x0 + 30, y0 - 10);
                    x0 += 75;
                    x1 += 75;
                }
            } else {
                if (bin.charAt(i) == '0') {
                    if (bin.charAt(i - 1) == '0') {
                        g.drawLine(x0, y0, x0 + 75, y0);
                        g.drawString("0", x0 + 30, y0 - 10);
                        x0 += 75;
                        x1 += 75;
                    } else {
                        g.drawLine(x1, y1, x0, y0);
                        g.drawLine(x0, y0, x0 + 75, y0);
                        g.drawString("0", x0 + 30, y0 - 10);
                        x0 += 75;
                        x1 += 75;
                    }
                } else {
                    if (bin.charAt(i - 1) == '1') {
                        g.drawLine(x1, y1, x1 + 75, y1);
                        g.drawString("1", x1 + 30, y1 - 10);
                        x0 += 75;
                        x1 += 75;
                    } else {
                        g.drawLine(x1, y1, x0, y0);
                        g.drawLine(x1, y1, x1 + 75, y1);
                        g.drawString("1", x1 + 30, y1 - 10);
                        x1 += 75;
                        x0 += 75;
                    }
                }
            }
        }
        if (bin.charAt(bin.length() - 1) == '1') {
            g.drawLine(x1, y1, x0, y0);
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            Scanner sc = new Scanner(System.in);
            System.out.println("Enter Binary String: ");
            String bin = sc.next();
            Unipolar l = new Unipolar(bin);
        });
    }
}
