import java.awt.*;
import javax.swing.*;
import java.util.*;
//NRZ Inverse
public class NRZI extends JFrame {

    String bin;

    public NRZI(String b) {
        this.bin = b;
        setSize(800, 800);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }

    public void paint(Graphics g) {
        super.paint(g);

        g.setColor(Color.BLACK);

        g.drawLine(75, 75, 75, 750);
        g.drawLine(75, 450, 750, 450);

        g.setColor(Color.RED);

        int x0 = 75, x1 = 75, y0 = 375, y1 = 525;

        g.drawString("High", 30, 400);
        g.drawString("Low", 30, 500);

        boolean up = true;

        for (int i = 0; i < bin.length(); i++) {
            if (bin.charAt(i) == '0') {
                if (up) {
                    g.drawLine(x0, y0, x0 + 75, y0);
                } else {
                    g.drawLine(x1, y1, x1 + 75, y1);
                }
            } else {
                if (up) {
                    g.drawLine(x0, y0, x1, y1);
                    g.drawLine(x1, y1, x1 + 75, y1);
                    up = false;
                } else {
                    g.drawLine(x1, y1, x0, y0);
                    g.drawLine(x0, y0, x0 + 75, y0);
                    up = true;
                }
            }
            x0 += 75;
            x1 += 75;
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            Scanner sc = new Scanner(System.in);
            System.out.print("Enter Binary String: ");
            String bin = sc.next();
            
            if (!bin.matches("[01]+")) {
                System.out.println("Invalid input. Please enter a binary string (containing only 0s and 1s).");
                return;
            }
            NRZI l = new NRZI(bin);
        });
    }
}
