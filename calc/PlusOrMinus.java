package calc;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class PlusOrMinus implements ActionListener {

	public CalcState state;
	
	public PlusOrMinus(CalcState s) {
		state = s;
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		state.plusOrMinus();
	}

}
