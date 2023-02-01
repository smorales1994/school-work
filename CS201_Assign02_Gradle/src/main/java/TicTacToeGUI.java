import java.awt.BorderLayout;

import javax.swing.JFrame;
import javax.swing.SwingUtilities;

/**
 * The TicTacToeGUI class is a "frame", which is a top-level window.
 * Its only purpose in this program is as a container for the
 * TicTacToePanel, which is where all of the gameplay and
 * GUI operations occur.
 * 
 * You won't need to change this class.
 */
public class TicTacToeGUI extends JFrame {
	private static final long serialVersionUID = 1L;
	public static void main(String[] args) {
		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				TicTacToeGUI app = new TicTacToeGUI();
				TicTacToePanel panel = new TicTacToePanel();
				panel.setFocusable(true);
				panel.requestFocusInWindow();
				app.getContentPane().add(panel, BorderLayout.CENTER);
				app.pack();
				app.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				app.setVisible(true);
			}
		});
	}
}
