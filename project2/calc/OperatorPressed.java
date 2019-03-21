package calc;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class OperatorPressed implements ActionListener {

	public CalcState state;
	public char op;
	
	public OperatorPressed(CalcState s, char i) {
		state = s;
		op = i;
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		if (op != '=') {
			state.lastOp = op;
		}
		state.lastButton = op;
		state.operate();
		
	}

}
