package calc;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ClearButton implements ActionListener {

	public CalcState state;
	
	public ClearButton(CalcState s) {
		state = s;
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		state.clear();
		state.lastButton = 'C';
	}

}
