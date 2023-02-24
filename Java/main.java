package Java;
import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import static javax.swing.JFrame.EXIT_ON_CLOSE;
import static javax.swing.WindowConstants.DISPOSE_ON_CLOSE;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.Border;

import java.awt.Color;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Image;
import java.net.URL;
import javax.swing.Box;
import javax.swing.ImageIcon;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
public class main extends JFrame implements ActionListener
{
    //Color
    public static final Color WHITE = new Color(255,255,255);
    public static final Color BLACK = new Color(0, 0, 0);
    public static final Color GRAY = new Color(128, 128, 128);
    public static final Color SLIVER = new Color(192, 192, 192);
    public static final Color Blue_VsCode = new Color(0, 120, 215);

    //Menu bar
    private JMenuBar mainBar;
    private JMenu moreMenu;
    private JMenuItem helpMenu;
    //JLabel
    private JLabel nameLabel;
    private JLabel picLabel;
    //JButton
    private JButton homeButton;
    private JButton helpButton;
    private JButton closeButton;
    //JPanel
    private JPanel centerPanel;
    private JPanel lefPanel;
    private JPanel rightPanel; 
    private JPanel upperPanel;
    private JPanel lowerPanel;
    //Gridlayout
    GridBagConstraints gbc = new GridBagConstraints();


    public main(){
        //Side of the windows
        super("C++ Libraries");
        this.setBounds(100, 100, 900, 700);

        this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        this.setLayout(new BorderLayout());

        //buttons
        this.homeButton = new JButton("Home");
        homeButton.addActionListener(this);
        homeButton.setBounds(10, 10, 10, 5);
        this.closeButton = new JButton("Close");
        closeButton.addActionListener(this);

        //panels
        this.centerPanel = new JPanel(new GridBagLayout());
        centerPanel.setBackground(WHITE);
        this.add(centerPanel, BorderLayout.CENTER);
        this.upperPanel = new JPanel(new FlowLayout());
        upperPanel.setBackground(GRAY);
        this.add(upperPanel, BorderLayout.NORTH);
        this.lowerPanel = new JPanel( new FlowLayout());
        lowerPanel.setBackground(GRAY);
        this.add(lowerPanel, BorderLayout.SOUTH);
        this.lefPanel = new JPanel(new GridBagLayout());
        this.add(lefPanel, BorderLayout.WEST);
        this.rightPanel = new JPanel(new GridBagLayout());
        this.add(rightPanel, BorderLayout.EAST);

        
        //add buttons to Panel
        //name of the program 
        gbc.gridx = 0;
        gbc.gridy = 0;
        
        //Adding home buttons
        gbc.gridy = 2;
        centerPanel.add(homeButton, gbc);
        //Adding close Buttom to bottom Panel 
        lowerPanel.add(closeButton);

        //Menu
        this.mainBar = new JMenuBar();
        mainBar.setBackground(GRAY);
        this.moreMenu = new JMenu("More");
        this.helpMenu = new JMenuItem("Help");
        helpMenu.addActionListener(this);
        moreMenu.add(helpMenu);
        mainBar.add(moreMenu);
        this.setJMenuBar(mainBar);
        
       
        this.setVisible(true);
    }

    public void actionPerformed(ActionEvent e){

    }


    public static void main(String[] args) {
        main objMain = new main(); 
    }
}





