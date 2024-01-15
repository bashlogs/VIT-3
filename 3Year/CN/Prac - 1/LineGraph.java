import javax.swing.*;
import java.awt.*;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LineGraph extends JFrame {
    private String data;
    private JComboBox<String> encodingSchemeComboBox;
    private JButton drawButton;

    public LineGraph() {
        setTitle("Line Coding Graph");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(800, 300);
        setLocationRelativeTo(null);
        setLayout(new FlowLayout());

        JLabel dataLabel = new JLabel("Enter the data elements:");
        JTextField dataTextField = new JTextField(20);
        String[] encodingSchemes = {"Unipolar", "Bipolar NRZI", "Bipolar NRZL", "Manchester", "Differential Manchester", "Polar"};
        encodingSchemeComboBox = new JComboBox<>(encodingSchemes);
        drawButton = new JButton("Draw Graph");

        add(dataLabel);
        add(dataTextField);
        add(encodingSchemeComboBox);
        add(drawButton);

        drawButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String data = dataTextField.getText();
                String selectedEncodingScheme = (String) encodingSchemeComboBox.getSelectedItem();
                if (data != null && !data.isEmpty()) {
                    switch (selectedEncodingScheme) {
                        case "Unipolar":
                            Unipolar unipolar = new Unipolar(data);
                            unipolar.setVisible(true);
                            break;
                        case "Bipolar NRZI":
                            Bipolar_NRZI bipolarNRZI = new Bipolar_NRZI(data);
                            bipolarNRZI.setVisible(true);
                            break;
                        case "Bipolar NRZL":
                            Bipolar_NRZL bipolarNRZL = new Bipolar_NRZL(data);
                            bipolarNRZL.setVisible(true);
                            break;
                        case "Manchester":
                            Manchester manchester = new Manchester(data);
                            manchester.setVisible(true);
                            break;
                        case "Differential Manchester":
                            DiffManchester diffManchester = new DiffManchester(data);
                            diffManchester.setVisible(true);
                            break;
                        case "Polar":
                            Polar polar = new Polar(data);
                            polar.setVisible(true);
                            break;
                    }
                } else {
                    JOptionPane.showMessageDialog(LineGraph.this, "Please enter the data elements.");
                }
            }
        });
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            LineGraph lineCodingGraph = new LineGraph();
            lineCodingGraph.setVisible(true);
        });
    }
}

class Unipolar extends JFrame {
    private String data;

    public Unipolar(String data) {
        this.data = data;

        setTitle("Unipolar Line Coding Graph");
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setSize(800, 200);
        setLocationRelativeTo(null);
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);

        int x = 50;
        int y;
        int lineWidth = 50;
        g.setColor(Color.RED);

        //axes
        g.drawLine(50, 0, 50, 160);
        g.drawLine(50, 160, 800, 160);
        g.setColor(Color.BLACK);

        char m = data.charAt(0);  //for adding vertical line
        for (char bit : data.toCharArray()) {
            if (bit == '0') {
                if (bit == m) {
                    y = 160;
                    g.drawLine(x, y, x + lineWidth, y);
                    x += lineWidth;
                } else {
                    g.drawLine(x, 80, x, 160);
                    y = 160;
                    g.drawLine(x, y, x + lineWidth, y);
                    x += lineWidth;
                    m = bit;
                }
            } else if (bit == '1') {
                if (bit == m) {
                    y = 80;
                    g.drawLine(x, y, x + lineWidth, y);
                    x += lineWidth;
                } else {
                    g.drawLine(x, 80, x, 160);
                    y = 80;
                    g.drawLine(x, y, x + lineWidth, y);
                    x += lineWidth;
                    m = bit;
                }
            }
        }
    }
}

class Bipolar_NRZI extends JFrame {
    private String data;

    public Bipolar_NRZI(String data) {
        this.data = data;

        setTitle("Bipolar NRZI Line Coding Graph");
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setSize(800, 200);
        setLocationRelativeTo(null);
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);

        int x = 50;
        int y;
        int lineWidth = 50;
        g.setColor(Color.RED);
        g.drawLine(50, 0, 50, 200);
        g.drawLine(50, 120, 800, 120);
        g.setColor(Color.BLACK);
        int m = 0;
        for (char bit : data.toCharArray()) {
            if (bit == '1') {
                if (m == 1) {
                    m = 0;
                } else {
                    m = 1;
                }
            }
            if (bit == '1') {
                g.drawLine(x, 80, x, 160);
            }
            if (m == 0) {
                y = 160;
                g.drawLine(x, y, x + lineWidth, y);
                x += lineWidth;
            } else {
                y = 80;
                g.drawLine(x, y, x + lineWidth, y);
                x += lineWidth;
            }
        }
    }
}

class Bipolar_NRZL extends JFrame {
    private String data;

    public Bipolar_NRZL(String data) {
        this.data = data;

        setTitle("Bipolar NRZL Line Coding Graph");
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setSize(800, 200);
        setLocationRelativeTo(null);
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);

        int x = 50;
        int y;
        int lineWidth = 50;
        g.setColor(Color.RED);
        g.drawLine(50, 0, 50, 200);
        g.drawLine(50, 120, 800, 120);
        g.setColor(Color.BLACK);
        char m = data.charAt(0);
        for (char bit : data.toCharArray()) {
            if (bit == '0') {
                if (bit == m) {
                    y = 160;
                    g.drawLine(x, y, x + lineWidth, y);
                    x += lineWidth;
                } else {
                    g.drawLine(x, 80, x, 160);
                    y = 160;
                    g.drawLine(x, y, x + lineWidth, y);
                    x += lineWidth;
                    m = bit;
                }
            } else if (bit == '1') {
                if (bit == m) {
                    y = 80;
                    g.drawLine(x, y, x + lineWidth, y);
                    x += lineWidth;
                } else {
                    g.drawLine(x, 80, x, 160);
                    y = 80;
                    g.drawLine(x, y, x + lineWidth, y);
                    x += lineWidth;
                    m = bit;
                }
            }
        }
    }
}

class Manchester extends JFrame {
    private String data;

    public Manchester(String data) {

        this.data = data;

        setTitle("Manchester Line Coding Graph");
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setSize(800, 200);
        setLocationRelativeTo(null);
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);

        int x = 50;
        int y;
        int lineWidth = 50;
        g.setColor(Color.RED);
        g.drawLine(50, 0, 50, 200);
        g.drawLine(50, 120, 800, 120);
        g.setColor(Color.BLACK);
        char m = data.charAt(0);
        if (m == '0') {
            m = '1';
        } else {
            m = '0';
        }
        for (char bit : data.toCharArray()) {
            if (bit == '0') {
                if (bit != m) {
                    y = 80;
                    g.drawLine(x, y, x + lineWidth/2, y);
                    x += lineWidth/2;
                    g.drawLine(x, 80, x, 160);
                    y = 160;
                    g.drawLine(x, y, x + lineWidth/2, y);
                    x += lineWidth/2;
                    m = bit;
                } else {
                    g.drawLine(x, 80, x, 160);
                    y = 80;
                    g.drawLine(x, y, x + lineWidth/2, y);
                    x += lineWidth/2;
                    g.drawLine(x, 80, x, 160);
                    y = 160;
                    g.drawLine(x, y, x + lineWidth/2, y);
                    x += lineWidth/2;
                }
            } else if (bit == '1') {
                if (bit != m) {
                    y = 160;
                    g.drawLine(x, y, x + lineWidth/2, y);
                    x += lineWidth/2;
                    g.drawLine(x, 80, x, 160);
                    y = 80;
                    g.drawLine(x, y, x + lineWidth/2, y);
                    x += lineWidth/2;
                    m = bit;
                } else {
                    g.drawLine(x, 80, x, 160);
                    y = 160;
                    g.drawLine(x, y, x + lineWidth/2, y);
                    x += lineWidth/2;
                    g.drawLine(x, 80, x, 160);
                    y = 80;
                    g.drawLine(x, y, x + lineWidth/2, y);
                    x += lineWidth/2;
                }
            }
        }
    }
}

class DiffManchester extends JFrame {
    private String data;

    public DiffManchester(String data) {
        this.data = data;

        setTitle("Differential Manchester Line Coding Graph");
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setSize(800, 200);
        setLocationRelativeTo(null);
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);

        int x = 50;
        int y;
        int lineWidth = 50;
        g.setColor(Color.RED);
        g.drawLine(50, 0, 50, 200);
        g.drawLine(50, 120, 800, 120);
        g.setColor(Color.BLACK);
        int m = 0;
        for (char bit : data.toCharArray()) {
            if (bit == '1') {
                if (m == 1) {
                    m = 0;
                } else {
                    m = 1;
                }
            }
            if (bit == '0') {
                g.drawLine(x, 80, x, 160);
            }
            if (m == 0) {
                y = 160;
                g.drawLine(x, y, x + lineWidth/2, y);
                x += lineWidth/2;
                g.drawLine(x, 80, x, 160);
                y = 80;
                g.drawLine(x, y, x + lineWidth/2, y);
                x += lineWidth/2;
            } else {
                y = 80;
                g.drawLine(x, y, x + lineWidth/2, y);
                x += lineWidth/2;
                g.drawLine(x, 80, x, 160);
                y = 160;
                g.drawLine(x, y, x + lineWidth/2, y);
                x += lineWidth/2;
            }
        }
    }
}

class Polar extends JFrame {
    private String data;

    public Polar(String data) {
        this.data = data;

        setTitle("Polar Line Coding Graph");
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setSize(800, 200);
        setLocationRelativeTo(null);
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);

        int x = 50;
        int y;
        int lineWidth = 50;
        g.setColor(Color.RED);
        g.drawLine(50, 0, 50, 200);
        g.drawLine(50, 120, 800, 120);
        g.setColor(Color.BLACK);

        char m = data.charAt(0);
        for (char bit : data.toCharArray()) {
            if (bit == '0') {
                y = 120;
                g.drawLine(x, y, x + lineWidth, y);
                x += lineWidth;
            } else if (bit == '1') {
                if (m == '0') {
                    y = 40;
                    g.drawLine(x, y, x, 80);
                    g.drawLine(x, 160, x + lineWidth, 160);
                } else {
                    y = 160;
                    g.drawLine(x, y, x, 120);
                    g.drawLine(x, 80, x + lineWidth, 80);
                }
                x += lineWidth;
                m = bit;
            }
        }
    }
}