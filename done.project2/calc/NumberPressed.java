package calc;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class NumberPressed implements ActionListener {

	public CalcState state;
	public int number;
	
	public NumberPressed(CalcState s, int i) {
		state = s;
		number = i;
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		 state.newNumber(number);
		 state.setDisplay();
		 //may have to change
		 state.lastButton = 'N';
	}

}
