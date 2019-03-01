package calc;

/**
 * SetUp
 * 
 * Class to set up and start the calculator, plus
 * facilities for test-driving the calculator.
 *
 * @author Thomas VanDrunen
 * CS 245, Wheaton College
 * June 27, 2014
*/
public class SetUp {

	
	
	/**
	 * Method for initializing the calculator internals and
	 * connecting them to the calculator face.
	 * @param face The component representing the user interface of 
	 * the calculator. 
	 */
	public static void setUpCalculator(CalculatorFace face) {

		CalcState state = new CalcState(face);
		face.addNumberActionListener(0, new NumberPressed(state, 0));
		face.addNumberActionListener(1, new NumberPressed(state, 1));
		face.addNumberActionListener(2, new NumberPressed(state, 2));
		face.addNumberActionListener(3, new NumberPressed(state, 3));
		face.addNumberActionListener(4, new NumberPressed(state, 4));
		face.addNumberActionListener(5, new NumberPressed(state, 5));
		face.addNumberActionListener(6, new NumberPressed(state, 6));
		face.addNumberActionListener(7, new NumberPressed(state, 7));
		face.addNumberActionListener(8, new NumberPressed(state, 8));
		face.addNumberActionListener(9, new NumberPressed(state, 9));
		face.addActionListener('.', new DecimalPressed(state));
		face.addActionListener('+',  new OperatorPressed(state, '+'));
		face.addActionListener('-',  new OperatorPressed(state, '-'));
		face.addActionListener('*',  new OperatorPressed(state, '*'));
		face.addActionListener('/',  new OperatorPressed(state, '/'));
		face.addActionListener('=',  new OperatorPressed(state, '='));
		face.addActionListener('C',  new ClearButton(state));
		face.addPlusMinusActionListener(new PlusOrMinus(state));
		
		
		// add code here that will have the effect of connecting
		// the given face to your calculator
		
		
	}
	
	
	/**
	 * This main method is for your testing of your calculator.
	 * It will *not* be used during grading. Any changes you make
	 * to this method will be ignored at grading.
	 */
	public static void main(String[] args) {
		setUpCalculator(new PlainCalculatorFace());
	}

}
