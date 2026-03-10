package programs;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.event.CaretEvent;
import javax.swing.event.CaretListener;

import base.Rational;

import panels.HuffmanPanel;

/**
 * Huffman sample applet
 * 
 * @author Piller Imre
 */
public class Huffman extends javax.swing.JFrame {

	private static final long serialVersionUID = 1L;

	private final Color INVALID_COLOR = new Color(255, 230, 230);
	
	private HuffmanPanel huffmanPanel;
	
	private int s;
	private ArrayList<Rational> probabilities;
	
	private boolean isValidInput;
		
	private class InputPanel extends JPanel {
		private JTextField codeLettersField;
		private JTextField probabilityField;
		private JButton calcButton;
		
		public InputPanel() {
			setBackground(new Color(210, 210, 210));
			createPanel();
			setVisible(true);
		}

		private void createPanel() {
			// Create code element number field
			add(new JLabel("s = "));
			codeLettersField = new JTextField("", 4);
			codeLettersField.addCaretListener(new CaretListener(){
				@Override
				public void caretUpdate(CaretEvent arg0) {
				}				
			});
			add(codeLettersField);
			
			// Create probability input field
			add(new JLabel("F = "));
			probabilityField = new JTextField("", 40);
			probabilityField.addCaretListener(new CaretListener() {
				@Override
				public void caretUpdate(CaretEvent e) {
				}				
			});
			add(probabilityField);

			// Create calculate button
			calcButton = new JButton("Ok");		
			calcButton.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					// Check input fields
					isValidInput = true;
					huffmanPanel.setErrorMessage(null);

					if (codeLettersField.getText().isEmpty()) {
						codeLettersField.setBackground(INVALID_COLOR);
						huffmanPanel.setErrorMessage("Az s érték megadása kötelező !");	
						isValidInput = false;

						return;
					}
					
					try {
						s = Integer.parseInt(codeLettersField.getText());
						if (s > 1) {
							codeLettersField.setBackground(Color.white);							
						}
						else {
							codeLettersField.setBackground(INVALID_COLOR);
							huffmanPanel.setErrorMessage("s értéke nem lehet kisebb mint 2 !");
							isValidInput = false;
							
							return;
						}
					}
					catch (Exception ex) {
						codeLettersField.setBackground(INVALID_COLOR);
						huffmanPanel.setErrorMessage("Az s érték formátuma nem megfelelő !");
						isValidInput = false;
						
						return;
					}

					if (probabilityField.getText().isEmpty()) {
						probabilityField.setBackground(INVALID_COLOR);
						isValidInput = false;
						huffmanPanel.setErrorMessage("Kérem adja meg az elemek eloszlását !");
						
						return;						
					}

					probabilities = Rational.parseList(probabilityField.getText());
					
					if (probabilities != null) {
						probabilityField.setBackground(Color.white);	

						// Check probability
						Rational sum = new Rational(0, 1);
						for (int i = 0; i < probabilities.size(); i++) {
							sum = sum.add(probabilities.get(i));
							
							// Set symbol names
							probabilities.get(i).setName("" + (char)('a' + i));							
						}
						
						if (sum.compareTo(Rational.ONE) != 0) {
							probabilityField.setBackground(INVALID_COLOR);
							huffmanPanel.setErrorMessage("A valószínűségek összegének pontosan 1-nek kell lennie !  összeg = " + sum.toString());
							isValidInput = false;
							
							return;
						}
					}
					else {
						probabilityField.setBackground(INVALID_COLOR);
						huffmanPanel.setErrorMessage("A valószínűségek megadása nem megfelelő !");
						isValidInput = false;
						
						return;
					}
					
					if (isValidInput == true) {
						huffmanPanel.setValues(s, probabilities);
					}
				}
			});
			add(calcButton);
		}
	}
	
	public void init() {
	}
	
	public Huffman() {
		setLayout(new BorderLayout());

		// Add main panel
		huffmanPanel = new HuffmanPanel();
		add(huffmanPanel);
		
		// Add input panel
		InputPanel inputPanel = new InputPanel();
		add(inputPanel, BorderLayout.NORTH);

		isValidInput = false;
	}
	
	public static void main(String args[]) {
        java.awt.EventQueue.invokeLater(new Runnable() {
              public void run() {
                   Huffman frame = new Huffman();
                   frame.setVisible(true);
              }
        });
	}
}
