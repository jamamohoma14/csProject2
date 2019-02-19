package calc;

public class CalcState {
	
	public CalculatorFace face;
	public String display = "";
	public String aNum = "";
	public String bNum = "";
	public String lastTerm = "";
	public char op = '0';
	public int toCalculate;
	public boolean equate = false;
	public float answer;
	public int plusOrMinus = 1;
	public char lastButton;
	public boolean decimal = false;
	
	
	public CalcState(CalculatorFace f) {
		face = f;
	}
	
	public void decimal() {	
	
		if (decimal == false) {
			if (equate == true) {
				bNum += ".";
			} else {
				aNum += ".";
			}
		}
		decimal = true;
	
	}
	
	public void plusOrMinus() {
		
		plusOrMinus *= -1;
		setDisplay();
	
	}
	
	public void operate() {
		
		aNum = String.valueOf(Float.valueOf(aNum) * plusOrMinus);
		plusOrMinus = 1;
		decimal = false;
		if (equate == false) {
			equate = true;
		} else if (op == '+') {
			add();
		} else if (op == '-') {
			subtract();
		} else if (op == '*') {
			multiply();
		} else if (op == '/') {
			divide();
		}
		
	}
	
	public void add() {
		System.out.print("aNum: " + aNum + " bNum: " + bNum + " lastTerm: " + lastTerm + "\n");
		if (bNum == "") {
			answer = Float.valueOf(aNum) + Float.valueOf(lastTerm);
		} else {
			answer = Float.valueOf(aNum) + Float.valueOf(bNum);
			lastTerm = bNum;	
		}
		equate();
		
	}
	
	public void subtract() {
		
		if (bNum == "") {
			answer = Float.valueOf(aNum) - Float.valueOf(lastTerm);
		} else {
			answer = Float.valueOf(aNum) - Float.valueOf(bNum);
			lastTerm = bNum;	
		}
		equate();
		
	}
	
	public void multiply() {

		if (bNum == "") {
			answer = Float.valueOf(aNum) * Float.valueOf(lastTerm);
		} else {
			answer = Float.valueOf(aNum) * Float.valueOf(bNum);
			lastTerm = bNum;	
		}
		equate();
		
	}
	
	public void divide() {

		if (bNum == "") {
			answer = Float.valueOf(aNum) / Float.valueOf(lastTerm);
		} else {
			answer = Float.valueOf(aNum) / Float.valueOf(bNum);
			lastTerm = bNum;
		}
		equate();
		
	}
	
	public void equate() {
		
		aNum = String.valueOf(plusOrMinus * answer);
		bNum = "";
		display = aNum;
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
		if (equate == false) {
			aNum += String.valueOf(i);
			display = aNum;
		} else {
			bNum += String.valueOf(i);
			display = bNum;
		}
		
		System.out.print("aNum: " + aNum + '\n');
		System.out.print("bNum: " + bNum + '\n');
		System.out.print("display: " + display + '\n');
		
	}
	
	public void clear() {
		
		System.out.print("Clearing...\n");
		display = "";
		aNum = "";
		bNum = "";
		op = '0';
		equate = false;
		face.writeToScreen("");
		
	}
	
}
