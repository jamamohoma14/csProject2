package calc;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class DecimalPressed implements ActionListener {

	public CalcState state;
	
	public DecimalPressed(CalcState s) {
		state = s;
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		state.decimal();
	}

}
