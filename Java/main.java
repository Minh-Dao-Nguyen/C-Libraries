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
import javax.swing.JComboBox;
import javax.swing.border.Border;

import java.awt.Color;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Image;
import java.net.URL;
import java.util.concurrent.Flow;

import javax.swing.Box;
import javax.swing.ImageIcon;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;

import javax.swing.JScrollPane;
import javax.swing.SwingConstants;

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
    private JLabel dataStructures_label;
    //JButton
    private JButton homeButton;
    private JButton helpButton;
    private JButton closeButton;
    //JPanel
    private JPanel centerPanel;
    private JPanel leftPanel;
    private JPanel rightPanel; 
    private JPanel upperPanel;
    private JPanel lowerPanel;
    //JCombo Box
    private JComboBox dataStructures_Box; 
    //Gridlayout
    GridBagConstraints gbc = new GridBagConstraints();


    public main(){
        /****************/
        //Side of the windows
        super("C++ Libraries");
        this.setBounds(100, 100, 900, 700);

        this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        this.setLayout(new BorderLayout());
        /****************/

        /****************/
        //buttons
        this.homeButton = new JButton("Home");
        homeButton.addActionListener(this);
        homeButton.setBounds(10, 10, 10, 5);
        this.closeButton = new JButton("Close");
        closeButton.addActionListener(this);
        /****************/

        /****************/
        //panels
        this.centerPanel = new JPanel();
        centerPanel.setBackground(WHITE);
        //this.add(centerPanel, BorderLayout.CENTER);
        this.upperPanel = new JPanel(new FlowLayout());
        upperPanel.setBackground(GRAY);
        this.add(upperPanel, BorderLayout.NORTH);
        this.lowerPanel = new JPanel( new FlowLayout());
        lowerPanel.setBackground(GRAY);
        this.add(lowerPanel, BorderLayout.SOUTH);
        this.leftPanel = new JPanel(new GridBagLayout());
        leftPanel.setBackground(GRAY);
        this.add(leftPanel, BorderLayout.WEST);
        this.rightPanel = new JPanel(new GridBagLayout());
        this.add(rightPanel, BorderLayout.EAST);
        /****************/
        

        /****************/
        //Left Panel

        //Selection of data structure
        String[] dataStructures = { "Selection","Hash Map", "Graph", "Binary Search Tree", "Doubly Linked List", "Priority Queue", "Vector", "String" };
        dataStructures_Box = new JComboBox(dataStructures);
        dataStructures_Box.setSelectedIndex(0);
        dataStructures_Box.addActionListener(this);
        dataStructures_label = new JLabel("Data Structure", SwingConstants.LEFT);
        gbc.gridx = 0;
        gbc.gridy = 0;
        leftPanel.add(dataStructures_label, gbc);
        gbc.gridy = 1;
        leftPanel.add(dataStructures_Box, gbc);


        /****************/


        /****************/
        //Menu
        this.mainBar = new JMenuBar();
        mainBar.setBackground(GRAY);
        this.moreMenu = new JMenu("More");
        this.helpMenu = new JMenuItem("Help");
        helpMenu.addActionListener(this);
        moreMenu.add(helpMenu);
        mainBar.add(moreMenu);
        this.setJMenuBar(mainBar);
        /****************/
        

        /****************/
        /* 
        hashMap hasMapObj = new hashMap();
        String data = hasMapObj.data("C++ Libraries/Hash Map/UnorderedMap.h");
        String formatted = hasMapObj.escape(data);
;       formatted = "<html><font size='2'>" + formatted + "</font></html>";
        JLabel label = new JLabel(formatted);
        //JLabel dataPrint= new JLabel(data);
        JPanel dataPanel = new JPanel(new FlowLayout());
        centerPanel.add(label);
        JScrollPane scrollFrame = new JScrollPane(centerPanel);
        centerPanel.setAutoscrolls(true);
        scrollFrame.getVerticalScrollBar().setUnitIncrement(16);
        this.add(scrollFrame);
        //this.add(centerPanel, BorderLayout.CENTER);
        //centerPanel.add(scrollFrame); 
         */
        /****************/
        JScrollPane scrollFrame = new JScrollPane(centerPanel);
        centerPanel.setAutoscrolls(true);
        scrollFrame.getVerticalScrollBar().setUnitIncrement(16);
        this.add(scrollFrame);

        this.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e){
        String command = e.getActionCommand();
        //Closing the program
        if (command.equals("Close"))
        {
            WarningClose objWarning = new WarningClose();
        }
        //Open help frame
        else if (command.equals("Help"))
        {
            Help objHelp = new Help();
        }
        //Box selection
        else if(command.equals("comboBoxChanged")){
            centerPanel.removeAll();
            String selection = dataStructures_Box.getSelectedItem().toString();
            DataDisplay dataDisplayOBJ = new DataDisplay();
            String data = dataDisplayOBJ.data(selection);
            String formatted = "<html><font size='2'>" + data + "</font></html>";
            JLabel label = new JLabel(formatted);
            //JLabel dataPrint= new JLabel(data);
            JPanel dataPanel = new JPanel(new FlowLayout());
            centerPanel.add(label);
            this.setVisible(true);
        }
    }


    public static void main(String[] args) {
        main objMain = new main(); 
    }
}





