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


namespace Lab1SGDB
{
    public partial class Form1 : Form
    {
        SqlConnection cs = new SqlConnection("Data Source=NANU\\SQLEXPRESS; Initial Catalog=aa; Integrated Security=True; TrustServerCertificate=True");
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
                // Check if a player is selected in dataGridView1
                if (dataGridView1.SelectedRows.Count == 0 || dataGridView1.CurrentRow == null)
                {
                    MessageBox.Show("Please select a player first before adding a contract.");
                    return;
                }

                // Get the selected player ID
                int selectedPlayerId = Convert.ToInt32(dataGridView1.SelectedRows[0].Cells["Pid"].Value);

                da.InsertCommand = new SqlCommand("INSERT INTO Contracts (Cid, Pid, Team_name, Start_d, Last_d, Salary) VALUES(@cid, @pid, @team, @start, @last, @salary)", cs);

                da.InsertCommand.Parameters.Add("@cid", SqlDbType.Int).Value = Int32.Parse(textBox1.Text);
                da.InsertCommand.Parameters.Add("@pid", SqlDbType.Int).Value = selectedPlayerId; // Use the selected player's ID
                da.InsertCommand.Parameters.Add("@team", SqlDbType.VarChar).Value = textBox2.Text;
                da.InsertCommand.Parameters.Add("@start", SqlDbType.Date).Value = DateTime.Parse(textBox3.Text);
                da.InsertCommand.Parameters.Add("@last", SqlDbType.Date).Value = DateTime.Parse(textBox4.Text);
                da.InsertCommand.Parameters.Add("@salary", SqlDbType.Decimal).Value = Decimal.Parse(textBox5.Text);

                if (cs.State != ConnectionState.Open)
                    cs.Open();

                da.InsertCommand.ExecuteNonQuery();
                MessageBox.Show("Contract added successfully for Player ID: " + selectedPlayerId);

                RefreshContractsGrid(selectedPlayerId);

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
        private void RefreshContractsGrid(int playerId)
        {
            try
            {
                if (cs.State != ConnectionState.Open)
                    cs.Open();

                SqlDataAdapter contractsDA = new SqlDataAdapter();
                contractsDA.SelectCommand = new SqlCommand("SELECT * FROM Contracts WHERE Pid = @Pid", cs);
                contractsDA.SelectCommand.Parameters.AddWithValue("@Pid", playerId);

                DataTable contractsTable = new DataTable("Contracts");
                contractsDA.Fill(contractsTable);

                dataGridView2.DataSource = contractsTable;
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
                // Check if any contract is selected
                if (dataGridView2.SelectedRows.Count == 0)
                {
                    MessageBox.Show("Please select a contract to update.");
                    return;
                }

                // Get the contract ID that needs to be updated
                int selectedContractId = Convert.ToInt32(dataGridView2.SelectedRows[0].Cells["Cid"].Value);

                da.UpdateCommand = new SqlCommand("UPDATE Contracts SET Team_name = @team, Start_d = @start, Last_d = @last, Salary = @salary WHERE Cid = @cid", cs);

                // Add parameters for all fields
                da.UpdateCommand.Parameters.Add("@team", SqlDbType.VarChar).Value = textBox2.Text;
                da.UpdateCommand.Parameters.Add("@start", SqlDbType.Date).Value = DateTime.Parse(textBox3.Text);
                da.UpdateCommand.Parameters.Add("@last", SqlDbType.Date).Value = DateTime.Parse(textBox4.Text);
                da.UpdateCommand.Parameters.Add("@salary", SqlDbType.Decimal).Value = Decimal.Parse(textBox5.Text);
                da.UpdateCommand.Parameters.Add("@cid", SqlDbType.Int).Value = selectedContractId;

                if (cs.State != ConnectionState.Open)
                    cs.Open();

                int rowsAffected = da.UpdateCommand.ExecuteNonQuery();
                cs.Close();

                if (rowsAffected >= 1)
                {
                    MessageBox.Show("Contract updated successfully.");

                    // Refresh the contracts grid - get the player ID from the selected contract
                    int playerId = Convert.ToInt32(dataGridView2.SelectedRows[0].Cells["Pid"].Value);
                    RefreshContractsGrid(playerId);
                }
                else
                {
                    MessageBox.Show("No contract was updated.");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Update error: " + ex.Message);
                if (cs.State == ConnectionState.Open)
                    cs.Close();
            }
        }

        // Delete Data
        private void buttonDelete_Click(object sender, EventArgs e)
        {
            try
            {
                // Check if any contract is selected
                if (dataGridView2.SelectedRows.Count == 0)
                {
                    MessageBox.Show("Please select a contract to delete.");
                    return;
                }

                // Show a confirmation dialog before deleting
                DialogResult dr = MessageBox.Show("Are you sure you want to delete this contract?\nThis action cannot be undone.",
                                                 "Confirm Deletion", MessageBoxButtons.YesNo, MessageBoxIcon.Warning);

                // If the user clicks 'Yes', proceed with deletion
                if (dr == DialogResult.Yes)
                {
                    int selectedContractId = Convert.ToInt32(dataGridView2.SelectedRows[0].Cells["Cid"].Value);
                    int playerId = Convert.ToInt32(dataGridView2.SelectedRows[0].Cells["Pid"].Value);

                    // Set up the Delete command
                    da.DeleteCommand = new SqlCommand("DELETE FROM Contracts WHERE Cid = @cid", cs);
                    da.DeleteCommand.Parameters.Add("@cid", SqlDbType.Int).Value = selectedContractId;

                    // Open connection, execute delete command, and close the connection
                    if (cs.State != ConnectionState.Open)
                        cs.Open();

                    int rowsAffected = da.DeleteCommand.ExecuteNonQuery();
                    cs.Close();

                    if (rowsAffected >= 1)
                    {
                        MessageBox.Show("Contract deleted successfully.");

                        // Refresh the contracts grid
                        RefreshContractsGrid(playerId);
                    }
                    else
                    {
                        MessageBox.Show("No contract was deleted.");
                    }
                }
                else
                {
                    // If the user clicks 'No', cancel the deletion
                    MessageBox.Show("Deletion cancelled.");
                }
            }
            catch (Exception ex)
            {
                // Handle exceptions
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

                da.SelectCommand = new SqlCommand("SELECT * FROM Players", cs);
                ds.Clear();
                da.Fill(ds, "Players");  
                dataGridView1.DataSource = ds.Tables["Players"];

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
                    if (dataGridView1.SelectedRows[0].Cells["Pid"].Value != DBNull.Value)
                    {
                        // Make sure connection is open
                        if (cs.State != ConnectionState.Open)
                            cs.Open();

                        int selectedPlayerId = Convert.ToInt32(dataGridView1.SelectedRows[0].Cells["Pid"].Value);

                        SqlDataAdapter contractsDA = new SqlDataAdapter();
                        contractsDA.SelectCommand = new SqlCommand("SELECT * FROM Contracts WHERE Pid = @Pid", cs);
                        contractsDA.SelectCommand.Parameters.AddWithValue("@Pid", selectedPlayerId);

                        DataTable contractsTable = new DataTable("Contracts");
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
