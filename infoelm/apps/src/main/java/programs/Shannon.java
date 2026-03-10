package programs;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.event.CaretEvent;
import javax.swing.event.CaretListener;

import panels.HuffmanPanel;
import panels.ShannonPanel;

import base.IntervalNode;
import base.Rational;

public class Shannon extends javax.swing.JFrame {

	private static final long serialVersionUID = 1L;

	private final Color INVALID_COLOR = new Color(255, 230, 230);
	
	// MODE = {
	//   0 : "Shannon-Fano",
	//   1 : "Gilbert-Moore"
	// }
	
	private boolean USE_WEIGHTS;
	private int MODE;
	
	private ShannonPanel shannonPanel;
	
	private int s;
	private ArrayList<Rational> probabilities;
	private ArrayList<Rational> weights;
	
	private boolean isValidInput;

	public void init() {
		// Use parameters
        /*
		String coding = getParameter("coding");
		if ("ShannonFano".equals(coding)) {
			MODE = 0;
		}
		else {
			MODE = 1;
		}
        */
        MODE = 0;
		
        /*
		String inputType = this.getParameter("inputType");
		if ("simple".equals(inputType)) {
			USE_WEIGHTS = false;
		}
		else {
			USE_WEIGHTS = true;			
		}
        */
		USE_WEIGHTS = true;			

		// Add main panel
		shannonPanel = new ShannonPanel();
		add(shannonPanel);
		
		// Add input panel
		InputPanel inputPanel = new InputPanel();
		add(inputPanel, BorderLayout.NORTH);

		// Add view panel
		ViewPanel viewPanel = new ViewPanel();
		add(viewPanel, BorderLayout.SOUTH);
		
		isValidInput = false;

	}
		
	private class InputPanel extends JPanel {
		private JTextField codeLettersField;
		private JTextField probabilityField;
		private JTextField weightField;
		private JButton calcButton;
		
		public InputPanel() {
			setBackground(new Color(210, 210, 210));
			createPanel();
			setVisible(true);
		}

		private void createPanel() {
			// Create code element number field
			if (USE_WEIGHTS == false) {
				add(new JLabel("s = "));
				codeLettersField = new JTextField("", 4);
				codeLettersField.addCaretListener(new CaretListener(){
					@Override
					public void caretUpdate(CaretEvent arg0) {
					}				
				});
				add(codeLettersField);
			}
			else {
				// Create weight input field
				add(new JLabel("AC = "));
				weightField = new JTextField("", 25);
				weightField.addCaretListener(new CaretListener() {
					@Override
					public void caretUpdate(CaretEvent e) {
					}
				});
				add(weightField);
			}
						
			// Create probability input field
			add(new JLabel("F = "));
			if (USE_WEIGHTS == false) {
				probabilityField = new JTextField("", 50);
			}
			else {
				probabilityField = new JTextField("", 25);				
			}
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
					shannonPanel.setErrorMessage(null);
					
					if (USE_WEIGHTS == false) {

						if (codeLettersField.getText().isEmpty()) {
							codeLettersField.setBackground(INVALID_COLOR);
							shannonPanel.setErrorMessage("Az s érték megadása kötelező !");	
							isValidInput = false;

							return;
						}
						
						try {
							s = Integer.parseInt(codeLettersField.getText());
							if (s > 1) {
								codeLettersField.setBackground(Color.white);							

								// Calculate weights
								weights = new ArrayList<Rational>();
								for (int i = 0; i < s; i++) {
									weights.add(new Rational(1, s));
								}
							}
							else {
								codeLettersField.setBackground(INVALID_COLOR);
								shannonPanel.setErrorMessage("s értéke nem lehet kisebb mint 2 !");
								isValidInput = false;
								
								return;
							}
						}
						catch (Exception ex) {
							codeLettersField.setBackground(INVALID_COLOR);
							shannonPanel.setErrorMessage("Az s érték formátuma nem megfelelő !");								
							isValidInput = false;

							return;
						}
					}
					else {

						if (weightField.getText().isEmpty()) {
							weightField.setBackground(INVALID_COLOR);
							shannonPanel.setErrorMessage("Kérem adja meg az additív költségeket !");	
							isValidInput = false;

							return;
						}

						weights = Rational.parseList(weightField.getText());
						
						if (weights != null) {
							weightField.setBackground(Color.white);	

							// Check weights
							Rational sum = new Rational(0, 1);
							for (int i = 0; i < weights.size(); i++) {
								sum = sum.add(weights.get(i));
								
								// Set symbol names
								weights.get(i).setName("" + (char)('a' + i));							
							}
							
							if (sum.compareTo(Rational.ONE) != 0) {
								weightField.setBackground(INVALID_COLOR);
								isValidInput = false;
								shannonPanel.setErrorMessage("Az additív költségek összegének pontosan 1-nek kell lennie !  összeg = " + sum.toString());
								
								return;
							}
						}
						else {
							weightField.setBackground(INVALID_COLOR);
							isValidInput = false;
						}
					}

					if (probabilityField.getText().isEmpty()) {
						probabilityField.setBackground(INVALID_COLOR);
						isValidInput = false;
						shannonPanel.setErrorMessage("Kérem adja meg az elemek eloszlását !");
						
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
							isValidInput = false;
							shannonPanel.setErrorMessage("A valószínűségek összegének pontosan 1-nek kell lennie !  összeg = " + sum.toString());
							
							return;
						}
					}
					else {
						probabilityField.setBackground(INVALID_COLOR);
						shannonPanel.setErrorMessage("A valószínűségek megadása nem megfelelő !");
						isValidInput = false;

						return;
					}
					
					// Pass values to panel
					if (isValidInput == true) {

						// Sort probabilities
						if (MODE == 0) {
							probabilities = Rational.sort(probabilities, "descending");
						}

						if (MODE == 0) {
							calcShannonFano();
						}
						else {
							calcGilbertMoore();
						}
					}
				}
			});
			add(calcButton);
		}
		
		// Shannon-Fano
		private void calcShannonFano() {
			ArrayList<Rational> points = new ArrayList<Rational>();
						
			Rational sum = Rational.ZERO;
			for (int i = 0; i < probabilities.size(); i++) {
				points.add(sum);
				sum = sum.add(probabilities.get(i));
			}
			
			shannonPanel.setValues(weights, points, probabilities);	
		}
		
		// Gilbert-Moore
		private void calcGilbertMoore() {
			ArrayList<Rational> points = new ArrayList<Rational>();

			Rational half = new Rational(1, 2);
			Rational sum = Rational.ZERO;
			for (int i = 0; i < probabilities.size(); i++) {
				points.add(sum.add(probabilities.get(i).multiply(half)));
				sum = sum.add(probabilities.get(i));
			}

			shannonPanel.setValues(weights, points, probabilities);
		}
	}

	// View panel class
	private class ViewPanel extends JPanel {

		private JComboBox modeComboBox;
		private JCheckBox codeTableCheckBox;
		
		public ViewPanel() {
			setBackground(new Color(210, 210, 210));

			// Add display mode combo box
			add(new JLabel("Megjelenítés: "));
			
			String modeString[] = {"intervallumok", "teljes kódfa"};
			modeComboBox = new JComboBox(modeString);
			modeComboBox.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					IntervalNode.setCodeTreeMode(modeComboBox.getSelectedIndex() == 1);
					shannonPanel.createTree();
				}
			});
			add(modeComboBox);
			
			codeTableCheckBox = new JCheckBox("kódtábla");
			codeTableCheckBox.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent arg0) {
					shannonPanel.setShowCodeTable(codeTableCheckBox.isSelected());
					shannonPanel.createTree();
				}
			});
			add(codeTableCheckBox);
			
			setVisible(true);
		}
	}
	
	public Shannon() {
		setLayout(new BorderLayout());
	}

	public static void main(String args[]) {
        java.awt.EventQueue.invokeLater(new Runnable() {
              public void run() {
                   Shannon frame = new Shannon();
                   frame.init();
                   frame.setVisible(true);
              }
        });
	}
}
