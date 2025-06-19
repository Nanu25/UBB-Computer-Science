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
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using System.Configuration;  

namespace Lab2SGDB
{
    public partial class Form1 : Form
    {
        SqlConnection cs;
        SqlDataAdapter da = new SqlDataAdapter();
        DataSet ds = new DataSet();
        public Form1()
        {
            InitializeComponent();

            string conString = ConfigurationManager.ConnectionStrings["cn"].ConnectionString;
            cs = new SqlConnection(conString);

            dataGridView1.SelectionChanged += dataGridView1_SelectionChanged;

            dataGridView1.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
        }

        private void buttonSelect_Click(object sender, EventArgs e)
        {
            try
            {
                string parentTableName = ConfigurationManager.AppSettings["ParentTableName"];
                string selectQuery = ConfigurationManager.AppSettings["SelectParentQuery"]; // Changed from SelectQuery to SelectParentQuery

                da.SelectCommand = new SqlCommand(selectQuery, cs);

                if (cs.State != ConnectionState.Open)
                    cs.Open();

                ds.Clear();
                da.Fill(ds, parentTableName);

                dataGridView1.DataSource = ds.Tables[parentTableName];
                dataGridView1.SelectionMode = DataGridViewSelectionMode.FullRowSelect;

                cs.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show($"{ConfigurationManager.AppSettings["ParentTableName"]} data error: " + ex.Message);

                // Ensure the connection is closed in case of error
                if (cs.State == ConnectionState.Open)
                    cs.Close();
            }
        }


        private void buttonDelete_Click(object sender, EventArgs e)
        {
            try
            {
                // Get configuration values
                string childTableName = ConfigurationManager.AppSettings["ChildTableName"];
                string childPrimaryKey = ConfigurationManager.AppSettings["ChildPrimaryKey"];
                string childForeignKey = ConfigurationManager.AppSettings["ChildForeignKey"];
                string deleteQuery = ConfigurationManager.AppSettings["DeleteQuery"];

                if (dataGridView2.SelectedRows.Count == 0)
                {
                    MessageBox.Show($"Please select a {childTableName.ToLower()} to delete.");
                    return;
                }

                int selectedChildId = Convert.ToInt32(dataGridView2.SelectedRows[0].Cells[childPrimaryKey].Value);
                int parentId = Convert.ToInt32(dataGridView2.SelectedRows[0].Cells[childForeignKey].Value);

                DialogResult dr = MessageBox.Show(
                    $"Are you sure you want to delete this {childTableName.ToLower()}?\nThis action cannot be undone.",
                    "Confirm Deletion",
                    MessageBoxButtons.YesNo,
                    MessageBoxIcon.Warning
                );

                if (dr == DialogResult.Yes)
                {
                    da.DeleteCommand = new SqlCommand(deleteQuery, cs);

                    string paramName = "@" + childPrimaryKey.ToLower();
                    da.DeleteCommand.Parameters.Add(paramName, SqlDbType.Int).Value = selectedChildId;

                    if (cs.State != ConnectionState.Open)
                        cs.Open();

                    int rowsAffected = da.DeleteCommand.ExecuteNonQuery();
                    cs.Close();

                    if (rowsAffected >= 1)
                    {
                        MessageBox.Show($"{childTableName} deleted successfully.");
                        RefreshChildGrid(parentId);
                    }
                    else
                    {
                        MessageBox.Show($"No {childTableName.ToLower()} was deleted.");
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
                // Get configuration values
                string parentTableName = ConfigurationManager.AppSettings["ParentTableName"];
                string parentPrimaryKey = ConfigurationManager.AppSettings["ParentPrimaryKey"];
                string childTableName = ConfigurationManager.AppSettings["ChildTableName"];
                string childPrimaryKey = ConfigurationManager.AppSettings["ChildPrimaryKey"];
                string childForeignKey = ConfigurationManager.AppSettings["ChildForeignKey"];
                string insertQuery = ConfigurationManager.AppSettings["InsertQuery"];
                string columnNamesStr = ConfigurationManager.AppSettings["ChildColumnNames"];
                string parameterNamesStr = ConfigurationManager.AppSettings["ColumnNamesInsertParameters"];

                if (dataGridView1.SelectedRows.Count == 0 || dataGridView1.CurrentRow == null)
                {
                    MessageBox.Show($"Please select a {parentTableName.ToLower()} first before adding a {childTableName.ToLower()}.");
                    return;
                }

                // Get the selected parent ID
                int selectedParentId = Convert.ToInt32(dataGridView1.SelectedRows[0].Cells[parentPrimaryKey].Value);

                // Create command using configured query
                SqlCommand cmd = new SqlCommand(insertQuery, cs);

                // Add the primary key parameter
                try
                {
                    cmd.Parameters.Add("@" + childPrimaryKey.ToLower(), SqlDbType.Int).Value = Int32.Parse(textBox1.Text);
                }
                catch (FormatException)
                {
                    MessageBox.Show($"Invalid {childTableName} ID. Please enter a valid number in the first field.");
                    return;
                }

                string[] columnNames = columnNamesStr.Split(',');
                bool foreignKeyInColumns = false;

                for (int i = 0; i < columnNames.Length; i++)
                {
                    if (columnNames[i].Trim() == childForeignKey)
                    {
                        foreignKeyInColumns = true;
                        break;
                    }
                }

                if (!foreignKeyInColumns)
                {
                    cmd.Parameters.Add("@" + childForeignKey.ToLower(), SqlDbType.Int).Value = selectedParentId;
                }

                // Get parameter names
                string[] parameterNames = parameterNamesStr.Split(',');

                int textBoxIndex = 2; // Starting from textBox2
                for (int i = 0; i < columnNames.Length; i++)
                {
                    string columnName = columnNames[i].Trim();
                    string paramName = parameterNames[i].Trim();
                    System.Windows.Forms.TextBox textBox = Controls["textBox" + textBoxIndex] as System.Windows.Forms.TextBox;

                    if (textBox == null)
                    {
                        MessageBox.Show($"Could not find textBox{textBoxIndex}");
                        return;
                    }

                    // Special handling for foreign key to avoid duplication
                    if (columnName == childForeignKey)
                    {
                        cmd.Parameters.Add(paramName, SqlDbType.Int).Value = selectedParentId;
                        textBoxIndex++;
                        continue;
                    }

                    // Handle different data types based on column name patterns
                    if (columnName.Contains("_d") || columnName.EndsWith("d") || columnName.Contains("date") || columnName.Contains("Date"))
                    {
                        try
                        {
                            cmd.Parameters.Add(paramName, SqlDbType.Date).Value = DateTime.Parse(textBox.Text);
                        }
                        catch (FormatException)
                        {
                            MessageBox.Show($"Invalid date format in field {columnName}");
                            return;
                        }
                    }
                    else if (columnName.Contains("Salary") || columnName.Contains("Price") || columnName.Contains("Amount") ||
                             columnName.Contains("Cost") || columnName.Contains("Rate"))
                    {
                        try
                        {
                            cmd.Parameters.Add(paramName, SqlDbType.Decimal).Value = Decimal.Parse(textBox.Text);
                        }
                        catch (FormatException)
                        {
                            MessageBox.Show($"Invalid decimal value in {columnName} field");
                            return;
                        }
                    }
                    else if (columnName.Contains("ID"))
                    {
                        try
                        {
                            // If this is the foreign key and we're getting user input for it
                            if (columnName == childForeignKey && !string.IsNullOrWhiteSpace(textBox.Text))
                            {
                                int foreignKeyValue;
                                if (!int.TryParse(textBox.Text, out foreignKeyValue))
                                {
                                    MessageBox.Show($"Invalid integer value for field {columnName}");
                                    return;
                                }
                                // Avoid adding duplicate parameter
                                if (!cmd.Parameters.Contains(paramName))
                                {
                                    cmd.Parameters.Add(paramName, SqlDbType.Int).Value = foreignKeyValue;
                                }
                            }
                            else
                            {
                                cmd.Parameters.Add(paramName, SqlDbType.Int).Value = int.Parse(textBox.Text);
                            }
                        }
                        catch (FormatException)
                        {
                            MessageBox.Show($"Invalid integer value in {columnName} field");
                            return;
                        }
                    }
                    else
                    {
                        cmd.Parameters.Add(paramName, SqlDbType.VarChar).Value = textBox.Text;
                    }

                    textBoxIndex++;
                }

                // Open connection, execute query, and close
                if (cs.State != ConnectionState.Open)
                    cs.Open();

                cmd.ExecuteNonQuery();

                MessageBox.Show($"{childTableName} added successfully for {parentTableName} ID: {selectedParentId}");
                RefreshChildGrid(selectedParentId);

                cs.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Insert error: " + ex.Message);
                if (cs.State == ConnectionState.Open)
                    cs.Close();
            }
        }

        private void buttonUpdate_Click(object sender, EventArgs e)
        {
            try
            {
                // Get configuration values
                string childTableName = ConfigurationManager.AppSettings["ChildTableName"];
                string childPrimaryKey = ConfigurationManager.AppSettings["ChildPrimaryKey"];
                string childForeignKey = ConfigurationManager.AppSettings["ChildForeignKey"];
                string updateQuery = ConfigurationManager.AppSettings["UpdateQuery"];
                string columnNamesStr = ConfigurationManager.AppSettings["ChildColumnNames"];
                string parameterNamesStr = ConfigurationManager.AppSettings["ColumnNamesInsertParameters"];

                // Check if a child record is selected
                if (dataGridView2.SelectedRows.Count == 0)
                {
                    MessageBox.Show($"Please select a {childTableName.ToLower()} to update.");
                    return;
                }

                // Get the selected IDs
                int selectedChildId = Convert.ToInt32(dataGridView2.SelectedRows[0].Cells[childPrimaryKey].Value);
                int parentId = Convert.ToInt32(dataGridView2.SelectedRows[0].Cells[childForeignKey].Value);

                // Create command using configured query
                da.UpdateCommand = new SqlCommand(updateQuery, cs);

                // Split column names and parameter names for dynamic handling
                string[] columnNames = columnNamesStr.Split(',');
                string[] parameterNames = parameterNamesStr.Split(',');

                // Determine start index for textboxes (assuming there's a consistent pattern for textbox naming)
                int textBoxStartIndex = 2; 

                // Add parameters for all fields that need to be updated
                for (int i = 0; i < columnNames.Length; i++)
                {
                    string columnName = columnNames[i].Trim();
                    string paramName = parameterNames[i].Trim();
                    int textBoxIndex = textBoxStartIndex + i;

                    System.Windows.Forms.TextBox textBox = Controls["textBox" + textBoxIndex] as System.Windows.Forms.TextBox;
                    if (textBox == null)
                    {
                        MessageBox.Show($"Could not find textBox{textBoxIndex}");
                        return;
                    }

                    // Handle different data types based on column name patterns
                    if (columnName.Contains("_d") || columnName.EndsWith("d") || columnName.Contains("date") || columnName.Contains("Date"))
                    {
                        try
                        {
                            da.UpdateCommand.Parameters.Add(paramName, SqlDbType.Date).Value = DateTime.Parse(textBox.Text);
                        }
                        catch (FormatException)
                        {
                            MessageBox.Show($"Invalid date format in field {columnName}");
                            return;
                        }
                    }
                    else if (columnName.Contains("Salary") || columnName.Contains("Price") || columnName.Contains("Amount") ||
                             columnName.Contains("Cost") || columnName.Contains("Rate"))
                    {
                        try
                        {
                            da.UpdateCommand.Parameters.Add(paramName, SqlDbType.Decimal).Value = Decimal.Parse(textBox.Text);
                        }
                        catch (FormatException)
                        {
                            MessageBox.Show($"Invalid decimal value in {columnName} field");
                            return;
                        }
                    }
                    else if (columnName.Contains("ID"))
                    {
                        try
                        {
                            da.UpdateCommand.Parameters.Add(paramName, SqlDbType.Int).Value = int.Parse(textBox.Text);
                        }
                        catch (FormatException)
                        {
                            MessageBox.Show($"Invalid integer value in {columnName} field");
                            return;
                        }
                    }
                    else
                    {
                        da.UpdateCommand.Parameters.Add(paramName, SqlDbType.VarChar).Value = textBox.Text;
                    }
                }

                // Add the primary key parameter for the WHERE clause
                string primaryKeyParam = "@" + childPrimaryKey.ToLower();
                da.UpdateCommand.Parameters.Add(primaryKeyParam, SqlDbType.Int).Value = selectedChildId;

                // Open connection if needed
                if (cs.State != ConnectionState.Open)
                    cs.Open();

                // Execute the command
                int rowsAffected = da.UpdateCommand.ExecuteNonQuery();

                // Close connection
                cs.Close();

                // Show result and refresh grid
                if (rowsAffected >= 1)
                {
                    MessageBox.Show($"{childTableName} updated successfully.");
                    RefreshChildGrid(parentId);
                }
                else
                {
                    MessageBox.Show($"No {childTableName.ToLower()} was updated.");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Update error: " + ex.Message);
                // Ensure connection is closed
                if (cs.State == ConnectionState.Open)
                    cs.Close();
            }
        }

    


        // Updated refresh method to be universal
        private void RefreshChildGrid(int parentId)
        {
            try
            {
                // Get configuration values
                string childTableName = ConfigurationManager.AppSettings["ChildTableName"];
                string childForeignKey = ConfigurationManager.AppSettings["ChildForeignKey"];
                string childSelectQuery = ConfigurationManager.AppSettings["SelectChildQuery"];

                // Ensure connection is open
                if (cs.State != ConnectionState.Open)
                    cs.Open();

                SqlDataAdapter childDataAdapter = new SqlDataAdapter();
                childDataAdapter.SelectCommand = new SqlCommand(childSelectQuery, cs);
                childDataAdapter.SelectCommand.Parameters.AddWithValue("@" + childForeignKey.ToLower(), parentId);

                // Fill the DataTable with the child data
                DataTable childTable = new DataTable(childTableName);
                childDataAdapter.Fill(childTable);

                // Set the DataGridView's data source
                dataGridView2.DataSource = childTable;
            }
            catch (Exception ex)
            {
                MessageBox.Show("Refresh error: " + ex.Message);
            }
            finally
            {
                // Ensure the connection is closed after the operation
                if (cs.State == ConnectionState.Open)
                    cs.Close();
            }
        }
        private void dataGridView1_SelectionChanged(object sender, EventArgs e)
        {
            if (dataGridView1.SelectedRows.Count == 1 && dataGridView1.CurrentRow != null)
            {
                try
                {
                    // Get configuration values
                    string parentPrimaryKey = ConfigurationManager.AppSettings["ParentPrimaryKey"];
                    string childForeignKey = ConfigurationManager.AppSettings["ChildForeignKey"];
                    string childTableName = ConfigurationManager.AppSettings["ChildTableName"];
                    string childSelectQuery = ConfigurationManager.AppSettings["SelectChildQuery"];

                    // Check if the primary key value exists
                    if (dataGridView1.SelectedRows[0].Cells[parentPrimaryKey].Value != DBNull.Value)
                    {
                        // Ensure connection is open
                        if (cs.State != ConnectionState.Open)
                            cs.Open();

                        // Get the selected ID dynamically using the primary key name from config
                        int selectedParentId = Convert.ToInt32(dataGridView1.SelectedRows[0].Cells[parentPrimaryKey].Value);

                        // Create the command with dynamic parameter name that matches the foreign key
                        SqlDataAdapter childDataAdapter = new SqlDataAdapter();
                        childDataAdapter.SelectCommand = new SqlCommand(childSelectQuery, cs);
                        childDataAdapter.SelectCommand.Parameters.AddWithValue("@" + childForeignKey.ToLower(), selectedParentId);

                        // Fill the DataTable with the child data
                        DataTable childTable = new DataTable(childTableName);
                        childDataAdapter.Fill(childTable);

                        // Set the DataGridView's data source
                        dataGridView2.DataSource = childTable;
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"{ConfigurationManager.AppSettings["ChildTableName"]} data error: " + ex.Message);
                }
                finally
                {
                    // Ensure the connection is closed after the operation
                    if (cs.State == ConnectionState.Open)
                        cs.Close();
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

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void buttonConnect_Click_1(object sender, EventArgs e)
        {

        }

        private void Form1_Load_1(object sender, EventArgs e)
        {

        }
    }

}