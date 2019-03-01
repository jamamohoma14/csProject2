package calc;

public class CalcState {
	
	public CalculatorFace face;
	public String display = "";
	public String currString = "";
	public float currTerm = 0;
	public float lastTerm = 0;
	public char lastOp = '-';
	public int toCalculate;
	public boolean equate = false;
	public float answer;
	public int plusOrMinus = 1;
	public char lastButton;
	public boolean decimal = false;
	
	
	public CalcState(CalculatorFace f) {
		face = f;
	}
	
	public void operate() {
		
		if (currString != "") {
			lastTerm = Float.valueOf(currString) * plusOrMinus;
			plusOrMinus = 1;
			decimal = false;
			if (equate == false) {
				equate = true;
			} else if (lastOp == '+') {
				add();
			} else if (lastOp == '-') {
				subtract();
			} else if (lastOp == '*') {
				multiply();
			} else if (lastOp == '/') {
				divide();
			}

		}
		
	}
	
	public void add() {
		
		lastTerm = lastTerm + Float.valueOf(currString);
		currString = "";	
		equate();
		
	}
	
	public void subtract() {
		
		lastTerm = lastTerm - Float.valueOf(currString);
		currString = "";	
		equate();
		
	}
	
	public void multiply() {

		lastTerm = lastTerm * Float.valueOf(currString);
		currString = "";	
		equate();
		
	}
	
	public void divide() {

		lastTerm = lastTerm / Float.valueOf(currString);
		currString = "";	
		equate();
		
	}
	
	public void equate() {
		
		currString = "";
		display = String.valueOf(lastTerm);
		setDisplay();
		
	}
	
	public void setDisplay() {
		
		Float tmp;
		if (display != "") {
			tmp = Float.valueOf(display) * plusOrMinus;
		} else {
			tmp = Float.valueOf(0);
		}
		face.writeToScreen(String.valueOf(tmp));
	
	}
	
	public void newNumber(int i) {
		
		if (lastButton == '=') {
			clear();
		}
		
		currString += String.valueOf(i);
		display = currString;
	}
	
	public void decimal() {	
	
		if (decimal == false) {
			currString += ".";
		}
		decimal = true;
	
	}
	
	public void plusOrMinus() {
		
		plusOrMinus *= -1;
		setDisplay();
	
	}
	
	public void clear() {
		
		display = "";
		currString = "";
		currTerm = 0;
		lastTerm = 0;
		lastOp = '-';
		equate = false;
		face.writeToScreen("");
		
	}
	
}
