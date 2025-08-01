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
using static System.Windows.Forms.VisualStyles.VisualStyleElement;


namespace SgdbS3;

public partial class Form1 : Form
{
	SqlConnection cs = new SqlConnection("Data Source=NANU\\SQLEXPRESS; Initial Catalog=SgdbT; Integrated Security=True; TrustServerCertificate=True");
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
			int selectedBookStoreId = Convert.ToInt32(dataGridView1.SelectedRows[0].Cells["Bsid"].Value);

			// Create the insert command
			da.InsertCommand = new SqlCommand("INSERT INTO Employers (Bsid, Name, Surname, Gender, Experience) VALUES (@Bsid, @name, @surname, @gender, @experience)", cs);

			da.InsertCommand.Parameters.Add("@Bsid", SqlDbType.Int).Value = selectedBookStoreId;
			da.InsertCommand.Parameters.Add("@name", SqlDbType.VarChar, 50).Value = textBox1.Text;
			da.InsertCommand.Parameters.Add("@experience", SqlDbType.Int).Value = int.Parse(textBox3.Text);
			da.InsertCommand.Parameters.Add("@surname", SqlDbType.VarChar, 50).Value = textBox2.Text;
			da.InsertCommand.Parameters.Add("@gender", SqlDbType.VarChar, 50).Value = textBox4.Text;

			// Open the connection if it's not already open
			if (cs.State != ConnectionState.Open)
				cs.Open();

			// Execute the insert
			da.InsertCommand.ExecuteNonQuery();

			MessageBox.Show("Employer added successfully for Publisher ID: " + selectedBookStoreId);

			RefreshBooksGrid(selectedBookStoreId); // Optional: Refresh posts view

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
	private void RefreshBooksGrid(int bookStoreId)
	{
		try
		{
			if (cs.State != ConnectionState.Open)
				cs.Open();

			SqlDataAdapter postsDA = new SqlDataAdapter();
			postsDA.SelectCommand = new SqlCommand("SELECT * FROM Employers WHERE Bsid = @Bsid", cs);
			postsDA.SelectCommand.Parameters.AddWithValue("@Bsid", bookStoreId);

			DataTable booksTable = new DataTable("BookStore");
			postsDA.Fill(booksTable);

			dataGridView2.DataSource = booksTable;
		}
		catch (Exception ex)
		{
			MessageBox.Show("Error refreshing employers: " + ex.Message);
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
			int selectedEmployerId = Convert.ToInt32(dataGridView2.SelectedRows[0].Cells["Eid"].Value);

			da.UpdateCommand = new SqlCommand("UPDATE Employers SET [Name] = @name, Surname = @surname, Gender = @gender, Experience = @experience WHERE Eid = @eid", cs);

			// Add parameters for all fields

			da.UpdateCommand.Parameters.Add("@Eid", SqlDbType.Int).Value = selectedEmployerId;
			da.UpdateCommand.Parameters.Add("@name", SqlDbType.VarChar, 50).Value = textBox1.Text;
			da.UpdateCommand.Parameters.Add("@experience", SqlDbType.Int).Value = int.Parse(textBox3.Text);
			da.UpdateCommand.Parameters.Add("@surname", SqlDbType.VarChar, 50).Value = textBox2.Text;
			da.UpdateCommand.Parameters.Add("@gender", SqlDbType.VarChar, 50).Value = textBox4.Text;

			if (cs.State != ConnectionState.Open)
				cs.Open();

			int rowsAffected = da.UpdateCommand.ExecuteNonQuery();
			cs.Close();

			if (rowsAffected >= 1)
			{
				MessageBox.Show("Employer updated successfully.");

				// Refresh posts grid - get the user ID from the selected post
				int publisherId = Convert.ToInt32(dataGridView2.SelectedRows[0].Cells["Bsid"].Value);
				RefreshBooksGrid(publisherId);
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
				MessageBox.Show("Please select an employer to delete.");
				return;
			}

			// Show a confirmation dialog before deleting
			DialogResult dr = MessageBox.Show("Are you sure you want to delete this post?\nThis action cannot be undone.",
											 "Confirm Deletion", MessageBoxButtons.YesNo, MessageBoxIcon.Warning);

			if (dr == DialogResult.Yes)
			{
				int selectedEmployerId = Convert.ToInt32(dataGridView2.SelectedRows[0].Cells["Eid"].Value);
				int bookStoreId = Convert.ToInt32(dataGridView2.SelectedRows[0].Cells["Bsid"].Value);

				// Set up the Delete command
				da.DeleteCommand = new SqlCommand("DELETE FROM Employers WHERE Eid = @eid", cs);
				da.DeleteCommand.Parameters.Add("@eid", SqlDbType.Int).Value = selectedEmployerId;

				// Open connection, execute delete command, and close the connection
				if (cs.State != ConnectionState.Open)
					cs.Open();

				int rowsAffected = da.DeleteCommand.ExecuteNonQuery();
				cs.Close();

				if (rowsAffected >= 1)
				{
					MessageBox.Show("Employer deleted successfully.");

					// Refresh the posts grid
					RefreshBooksGrid(bookStoreId);
				}
				else
				{
					MessageBox.Show("No employer was deleted.");
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

			da.SelectCommand = new SqlCommand("SELECT * FROM BookStore", cs);
			ds.Clear();
			da.Fill(ds, "BookStore");
			dataGridView1.DataSource = ds.Tables["BookStore"];
			dataGridView1.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
		}
		catch (Exception ex)
		{
			MessageBox.Show("Books data error: " + ex.Message);
		}
	}

	private void dataGridView1_SelectionChanged(object sender, EventArgs e)
	{
		if (dataGridView1.SelectedRows.Count == 1 && dataGridView1.CurrentRow != null)
		{
			try
			{
				if (dataGridView1.SelectedRows[0].Cells["Bsid"].Value != DBNull.Value)
				{
					// Make sure connection is open
					if (cs.State != ConnectionState.Open)
						cs.Open();

					int selectedBookStoreId = Convert.ToInt32(dataGridView1.SelectedRows[0].Cells["Bsid"].Value);

					SqlDataAdapter bookStoreDA = new SqlDataAdapter();
					bookStoreDA.SelectCommand = new SqlCommand("SELECT * FROM Employers WHERE Bsid = @Bsid", cs);
					bookStoreDA.SelectCommand.Parameters.AddWithValue("@Bsid", selectedBookStoreId);

					DataTable contractsTable = new DataTable("BookStore");
					bookStoreDA.Fill(contractsTable);

					dataGridView2.DataSource = contractsTable;

				}
			}
			catch (Exception ex)
			{
				MessageBox.Show("Books data error: " + ex.Message);
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

