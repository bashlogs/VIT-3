import java.awt.event.*;
import java.awt.*;
import javax.swing.*;

public class LineCoding extends JFrame implements ActionListener {
    public int x1 = 300, x2 = 300, y1 = 100, y2 = 100;
    int[] baud;
    int[] bit;
    JTextField inpData = new JTextField(12);
    JComboBox<String> techniques = null;
    JPanel drawPanel = new JPanel();

    public LineCoding() {
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setSize(700, 400);
        setTitle("Line Coding Techniques");
        initComponents();
    }

    private void initComponents() {
        JPanel topPanel = new JPanel();
        topPanel.add(new JLabel("Input Data:"));
        topPanel.add(inpData);
        String list[] = {
                "Manchester",
                "Differential Manchester",
                "Bipolar NRZ"
        };
        techniques = new JComboBox<String>(list);
        topPanel.add(new JLabel("Technique: "));
        topPanel.add(techniques);
        JButton encodeBtn = new JButton("Encode");
        JButton clrBtn = new JButton("Clear");
        topPanel.add(encodeBtn);
        encodeBtn.addActionListener(this);
        topPanel.add(clrBtn);
        clrBtn.addActionListener(this);
        drawPanel.setBackground(Color.WHITE);
        add(drawPanel);
        add(topPanel, BorderLayout.NORTH);
    }

    public static void main(String[] args) {
        new LineCoding().setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getActionCommand().equals("Encode"))
            encode();
        else if (e.getActionCommand().equals("Clear"))
            repaint();
    }

    private void encode() {
        drawPanel.getGraphics().clearRect(0, 0, drawPanel.getWidth(), drawPanel.getHeight()); // Clear the panel
        drawPanel.getGraphics().drawString(techniques.getSelectedItem() + " Encoding Technique!", 400, 40);
        char data[] = inpData.getText().toCharArray();
        int loop = 1;
        boolean flag = true;
        switch ((String) techniques.getSelectedItem()) {
            case "Bipolar NRZ":
                baud = new int[data.length + 2];
                baud[0] = 0;
                baud[baud.length - 1] = 0;
                for (int i = 0; i < data.length; i++) {
                    if (data[i] == '1') {
                        if (flag) {
                            baud[loop] = 50;
                            flag = false;
                        } else {
                            baud[loop] = -50;
                            flag = true;
                        }
                    } else
                        baud[loop] = 0;
                    loop++;
                }
                draw(baud);
                break;
            case "Manchester [IEEE]":
                baud = new int[(data.length * 2) + 2];
                baud[0] = 0;
                for (int i = 0; i < data.length; i++) {
                    if (data[i] == '1') {
                        baud[loop] = -50;
                        baud[loop + 1] = 50;
                    } else {
                        baud[loop] = 50;
                        baud[loop + 1] = -50;
                    }
                    loop += 2;
                }
                draw(baud);
                break;
            case "Differential Manchester":
                baud = new int[(data.length * 2) + 2];
                baud[0] = 0;
                for (int i = 0; i < data.length; i++) {
                    if (data[i] == '1') {
                        if (flag && baud[loop - 1] != -50) {
                            baud[loop] = 50;
                            baud[loop + 1] = -50;
                            flag = false;
                        } else {
                            baud[loop] = -50;
                            baud[loop + 1] = 50;
                            flag = true;
                        }
                    } else {
                        baud[loop] = 50;
                        baud[loop + 1] = -50;
                    }
                    loop += 2;
                }
                draw(baud);
                break;
        }
    }

    private void draw(int[] baud) {
        for (int i = 0; i < baud.length; i++) {
            if (baud[i] == 100 - y1) {
                y2 = y1;
                x2 = x1 + 30;
                drawPanel.getGraphics().drawLine(x1, y1, x2, y2);
            } else {
                x2 = x1;
                y2 = 100 - baud[i];
                drawPanel.getGraphics().drawLine(x1, y1, x2, y2);
                y1 = y2;
                x2 = x1 + 30;
                drawPanel.getGraphics().drawLine(x1, y1, x2, y2);
            }
            x1 = x2;
            y1 = y2;
        }
        x1 = 300;
        y1 = 100;
    }
}
