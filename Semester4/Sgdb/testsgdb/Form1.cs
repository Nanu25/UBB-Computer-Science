using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;
using Microsoft.Data.SqlClient;


namespace testsgdb
{
	public partial class Form1 : Form
	{
		SqlConnection cs = new SqlConnection("Data Source=NANU\\SQLEXPRESS; Initial Catalog=MiniFb; Integrated Security=True; TrustServerCertificate=True");
		SqlDataAdapter da = new SqlDataAdapter();
		DataSet ds = new DataSet();

		public Form1()
		{
			InitializeComponent();

			dataGridView1.SelectionChanged += dataGridView1_SelectionChanged;

			// Set selection mode to full row select
			dataGridView1.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
		}

		// Connect to Database
		private void buttonConnect_Click(object sender, EventArgs e)
		{
			try
			{
				cs.Open();
				MessageBox.Show("Connected to the Database!");

				cs.Close();
			}
			catch (Exception ex)
			{
				MessageBox.Show("Error: " + ex.Message);
			}
		}

		// Insert Data
		private void buttonInsert_Click(object sender, EventArgs e)
		{
			try
			{
				// Check if a user is selected in dataGridView1
				if (dataGridView1.SelectedRows.Count == 0 || dataGridView1.CurrentRow == null)
				{
					MessageBox.Show("Please select a user first before adding a post.");
					return;
				}

				// Get the selected user ID
				int selectedUserId = Convert.ToInt32(dataGridView1.SelectedRows[0].Cells["Uid"].Value);

				// Create the insert command
				da.InsertCommand = new SqlCommand("INSERT INTO Posts (Uid, Date, Text, Shares) VALUES (@uid, @date, @text, @shares)", cs);

				da.InsertCommand.Parameters.Add("@uid", SqlDbType.Int).Value = selectedUserId;
				da.InsertCommand.Parameters.Add("@date", SqlDbType.DateTime).Value = DateTime.Parse(textBox3.Text);
				da.InsertCommand.Parameters.Add("@text", SqlDbType.VarChar, 50).Value = textBox2.Text;
				da.InsertCommand.Parameters.Add("@shares", SqlDbType.Int).Value = int.Parse(textBox4.Text);

				// Open the connection if it's not already open
				if (cs.State != ConnectionState.Open)
					cs.Open();

				// Execute the insert
				da.InsertCommand.ExecuteNonQuery();

				MessageBox.Show("Post added successfully for User ID: " + selectedUserId);

				RefreshPostsGrid(selectedUserId); // Optional: Refresh posts view

				cs.Close();
			}
			catch (Exception ex)
			{
				MessageBox.Show("Insert error: " + ex.Message);
				if (cs.State == ConnectionState.Open)
					cs.Close();
			}
		}


		// Helper method to refresh the contracts grid for a specific player
		private void RefreshPostsGrid(int userId)
		{
			try
			{
				if (cs.State != ConnectionState.Open)
					cs.Open();

				SqlDataAdapter postsDA = new SqlDataAdapter();
				postsDA.SelectCommand = new SqlCommand("SELECT * FROM Posts WHERE Uid = @Uid", cs);
				postsDA.SelectCommand.Parameters.AddWithValue("@Uid", userId);

				DataTable postsTable = new DataTable("Posts");
				postsDA.Fill(postsTable);

				dataGridView2.DataSource = postsTable;
			}
			catch (Exception ex)
			{
				MessageBox.Show("Error refreshing contracts: " + ex.Message);
			}
		}

		private void buttonUpdate_Click(object sender, EventArgs e)
		{
			try
			{
				// Check if any post is selected
				if (dataGridView2.SelectedRows.Count == 0)
				{
					MessageBox.Show("Please select a post to update.");
					return;
				}

				// Get the post ID that needs to be updated
				int selectedPostId = Convert.ToInt32(dataGridView2.SelectedRows[0].Cells["Pid"].Value);

				da.UpdateCommand = new SqlCommand("UPDATE Posts SET [Text] = @text, [Date] = @date, Shares = @shares WHERE Pid = @pid", cs);

				// Add parameters for all fields
				da.UpdateCommand.Parameters.Add("@text", SqlDbType.VarChar).Value = textBox2.Text;
				da.UpdateCommand.Parameters.Add("@date", SqlDbType.Date).Value = DateTime.Parse(textBox3.Text);
				da.UpdateCommand.Parameters.Add("@shares", SqlDbType.Int).Value = Int32.Parse(textBox4.Text);
				da.UpdateCommand.Parameters.Add("@pid", SqlDbType.Int).Value = selectedPostId;

				if (cs.State != ConnectionState.Open)
					cs.Open();

				int rowsAffected = da.UpdateCommand.ExecuteNonQuery();
				cs.Close();

				if (rowsAffected >= 1)
				{
					MessageBox.Show("Post updated successfully.");

					// Refresh posts grid - get the user ID from the selected post
					int userId = Convert.ToInt32(dataGridView2.SelectedRows[0].Cells["Uid"].Value);
					RefreshPostsGrid(userId);
				}
				else
				{
					MessageBox.Show("No post was updated.");
				}
			}
			catch (Exception ex)
			{
				MessageBox.Show("Update error: " + ex.Message);
				if (cs.State == ConnectionState.Open)
					cs.Close();
			}
		}


		private void buttonDelete_Click(object sender, EventArgs e)
		{
			try
			{
				// Check if any post is selected
				if (dataGridView2.SelectedRows.Count == 0)
				{
					MessageBox.Show("Please select a post to delete.");
					return;
				}

				// Show a confirmation dialog before deleting
				DialogResult dr = MessageBox.Show("Are you sure you want to delete this post?\nThis action cannot be undone.",
												 "Confirm Deletion", MessageBoxButtons.YesNo, MessageBoxIcon.Warning);

				if (dr == DialogResult.Yes)
				{
					int selectedPostId = Convert.ToInt32(dataGridView2.SelectedRows[0].Cells["Pid"].Value);
					int userId = Convert.ToInt32(dataGridView2.SelectedRows[0].Cells["Uid"].Value);

					// Set up the Delete command
					da.DeleteCommand = new SqlCommand("DELETE FROM Posts WHERE Pid = @pid", cs);
					da.DeleteCommand.Parameters.Add("@pid", SqlDbType.Int).Value = selectedPostId;

					// Open connection, execute delete command, and close the connection
					if (cs.State != ConnectionState.Open)
						cs.Open();

					int rowsAffected = da.DeleteCommand.ExecuteNonQuery();
					cs.Close();

					if (rowsAffected >= 1)
					{
						MessageBox.Show("Post deleted successfully.");

						// Refresh the posts grid
						RefreshPostsGrid(userId);
					}
					else
					{
						MessageBox.Show("No post was deleted.");
					}
				}
				else
				{
					MessageBox.Show("Deletion cancelled.");
				}
			}
			catch (Exception ex)
			{
				MessageBox.Show("Delete error: " + ex.Message);
				if (cs.State == ConnectionState.Open)
					cs.Close();
			}
		}

		private void buttonSelect_Click(object sender, EventArgs e)
		{
			try
			{
				if (cs.State != ConnectionState.Open)
					cs.Open();

				da.SelectCommand = new SqlCommand("SELECT * FROM Users", cs);
				ds.Clear();
				da.Fill(ds, "Users");
				dataGridView1.DataSource = ds.Tables["Users"];
				dataGridView1.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
			}
			catch (Exception ex)
			{
				MessageBox.Show("Players data error: " + ex.Message);
			}
		}

		private void dataGridView1_SelectionChanged(object sender, EventArgs e)
		{
			if (dataGridView1.SelectedRows.Count == 1 && dataGridView1.CurrentRow != null)
			{
				try
				{
					if (dataGridView1.SelectedRows[0].Cells["Uid"].Value != DBNull.Value)
					{
						// Make sure connection is open
						if (cs.State != ConnectionState.Open)
							cs.Open();

						int selectedUserId = Convert.ToInt32(dataGridView1.SelectedRows[0].Cells["Uid"].Value);

						SqlDataAdapter contractsDA = new SqlDataAdapter();
						contractsDA.SelectCommand = new SqlCommand("SELECT * FROM Posts WHERE Uid = @Uid", cs);
						contractsDA.SelectCommand.Parameters.AddWithValue("@Uid", selectedUserId);

						DataTable contractsTable = new DataTable("Posts");
						contractsDA.Fill(contractsTable);

						dataGridView2.DataSource = contractsTable;

					}
				}
				catch (Exception ex)
				{
					MessageBox.Show("Contracts data error: " + ex.Message);
				}
			}
		}


		private void textBox2_TextChanged(object sender, EventArgs e)
		{

		}

		private void Form1_Load(object sender, EventArgs e)
		{

		}

		private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
		{

		}
	}
}

