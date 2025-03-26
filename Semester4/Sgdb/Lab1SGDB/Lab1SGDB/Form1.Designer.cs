namespace Lab1SGDB
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;
        private TextBox textBox1;
        private TextBox textBox2;
        private TextBox textBox3;
        private TextBox textBox4;
        private System.Windows.Forms.DataGridView dataGridView1, dataGridView2;
        private Button buttonConnect, buttonSelect, buttonInsert, buttonDelete, buttonUpdate;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            textBox1 = new TextBox();
            textBox2 = new TextBox();
            textBox3 = new TextBox();
            textBox4 = new TextBox();
            dataGridView1 = new DataGridView();
            textBox5 = new TextBox();
            buttonConnect = new Button();
            buttonInsert = new Button();
            buttonUpdate = new Button();
            buttonDelete = new Button();
            buttonSelect = new Button();
            dataGridView2 = new DataGridView();
            ((System.ComponentModel.ISupportInitialize)dataGridView1).BeginInit();
            ((System.ComponentModel.ISupportInitialize)dataGridView2).BeginInit();
            SuspendLayout();


            Label label1 = new Label();
            label1.AutoSize = true;
            label1.Location = new Point(30, 236);
            label1.Name = "label1";
            label1.Size = new Size(30, 20);
            label1.Text = "Cid";
            // 
            // textBox1
            // 
            textBox1.Location = new Point(112, 233);
            textBox1.Name = "textBox1";
            textBox1.Size = new Size(100, 27);
            textBox1.TabIndex = 0;

            Label label2 = new Label();
            label2.AutoSize = true;
            label2.Location = new Point(30, 279);
            label2.Name = "label2";
            label2.Size = new Size(80, 20);
            label2.Text = "Team Name";
            // 
            // textBox2
            // 
            textBox2.Location = new Point(112, 276);
            textBox2.Name = "textBox2";
            textBox2.Size = new Size(100, 27);
            textBox2.TabIndex = 1;
            textBox2.TextChanged += textBox2_TextChanged;

            Label label3 = new Label();
            label3.AutoSize = true;
            label3.Location = new Point(30, 329);
            label3.Name = "label3";
            label3.Size = new Size(72, 20);
            label3.Text = "Start Date";
            // 
            // textBox3
            // 
            textBox3.Location = new Point(112, 326);
            textBox3.Name = "textBox3";
            textBox3.Size = new Size(100, 27);
            textBox3.TabIndex = 2;

            Label label4 = new Label();
            label4.AutoSize = true;
            label4.Location = new Point(30, 386);
            label4.Name = "label4";
            label4.Size = new Size(65, 20);
            label4.Text = "End Date";

            // 
            // textBox4
            // 
            textBox4.Location = new Point(112, 383);
            textBox4.Name = "textBox4";
            textBox4.Size = new Size(100, 27);
            textBox4.TabIndex = 3;
            // 
            // dataGridView1
            // 
            dataGridView1.ColumnHeadersHeight = 29;
            dataGridView1.Location = new Point(395, 12);
            dataGridView1.Name = "dataGridView1";
            dataGridView1.RowHeadersWidth = 51;
            dataGridView1.Size = new Size(692, 341);
            dataGridView1.TabIndex = 4;
            dataGridView1.CellContentClick += dataGridView1_CellContentClick;

            Label label5 = new Label();
            label5.AutoSize = true;
            label5.Location = new Point(30, 430);
            label5.Name = "label5";
            label5.Size = new Size(50, 20);
            label5.Text = "Salary";
            // 
            // textBox5
            // 
            textBox5.Location = new Point(112, 433);
            textBox5.Name = "textBox5";
            textBox5.Size = new Size(100, 27);
            textBox5.TabIndex = 5;
            // 
            // buttonConnect
            // 
            buttonConnect.Location = new Point(237, 220);
            buttonConnect.Name = "buttonConnect";
            buttonConnect.Size = new Size(100, 40);
            buttonConnect.TabIndex = 6;
            buttonConnect.Text = "Connect";
            buttonConnect.Click += buttonConnect_Click;
            // 
            // buttonInsert
            // 
            buttonInsert.Location = new Point(237, 272);
            buttonInsert.Name = "buttonInsert";
            buttonInsert.Size = new Size(100, 40);
            buttonInsert.TabIndex = 7;
            buttonInsert.Text = "Insert";
            buttonInsert.Click += buttonInsert_Click;
            // 
            // buttonUpdate
            // 
            buttonUpdate.Location = new Point(237, 322);
            buttonUpdate.Name = "buttonUpdate";
            buttonUpdate.Size = new Size(100, 40);
            buttonUpdate.TabIndex = 8;
            buttonUpdate.Text = "Update";
            buttonUpdate.Click += buttonUpdate_Click;
            // 
            // buttonDelete
            // 
            buttonDelete.Location = new Point(237, 376);
            buttonDelete.Name = "buttonDelete";
            buttonDelete.Size = new Size(100, 40);
            buttonDelete.TabIndex = 9;
            buttonDelete.Text = "Delete";
            buttonDelete.Click += buttonDelete_Click;
            // 
            // buttonSelect
            // 
            buttonSelect.Location = new Point(237, 426);
            buttonSelect.Name = "buttonSelect";
            buttonSelect.Size = new Size(100, 40);
            buttonSelect.TabIndex = 10;
            buttonSelect.Text = "Display ";
            buttonSelect.Click += buttonSelect_Click;
            // 
            // dataGridView2
            // 
            dataGridView2.ColumnHeadersHeight = 29;
            dataGridView2.Location = new Point(395, 359);
            dataGridView2.Name = "dataGridView2";
            dataGridView2.RowHeadersWidth = 51;
            dataGridView2.Size = new Size(692, 261);
            dataGridView2.TabIndex = 11;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1119, 663);
            Controls.Add(buttonConnect);
            Controls.Add(buttonInsert);
            Controls.Add(buttonUpdate);
            Controls.Add(buttonDelete);
            Controls.Add(buttonSelect);
            Controls.Add(textBox5);
            Controls.Add(textBox1);
            Controls.Add(textBox2);
            Controls.Add(textBox3);
            Controls.Add(textBox4);
            Controls.Add(dataGridView2);
            Controls.Add(dataGridView1);
            this.Controls.Add(label1);
            this.Controls.Add(label2);
            this.Controls.Add(label3);
            this.Controls.Add(label4);
            this.Controls.Add(label5);  
            Name = "Form1";
            Text = "Form1";
            Load += Form1_Load;
            ((System.ComponentModel.ISupportInitialize)dataGridView1).EndInit();
            ((System.ComponentModel.ISupportInitialize)dataGridView2).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }


        #endregion

        private TextBox textBox5;
    }
}
