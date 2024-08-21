library(shiny)
library(shinydashboard)
library(tidyverse)
library(ggplot2)
library(viridis)
library(plotly)
library(dplyr)
#library(scales)


sales <- read.csv("C:\\UMPSA_Y2S2\\BSD2223 DSP II\\DSPII_Project\\sales_data.csv")

library(anytime)

# Convert "Date" column to yyyy-mm-dd format
sales$Date <- anydate(sales$Date)

# Convert "Date" column to Date type
sales$Date <- as.Date(sales$Date)


ui <- dashboardPage(
  dashboardHeader(title="Sales of Supermarket"),
  dashboardSidebar(
    
    sidebarMenu(
      menuItem("Cover Page", tabName = "dash1", icon = icon("home")),
      menuItem("Demographic Analysis", tabName = "dash2", icon = icon("users")),
      menuItem("Sales Analysis", tabName = "dash3", icon = icon("chart-bar")),
      menuItem("Gross Income Analysis", tabName = "dash4", icon = icon("dollar-sign")),
      menuItem("Summary", tabName = "summ", icon = icon("clipboard-list"))
      
    )
  ),
  
  dashboardBody(
    
    tabItems(
      tabItem(
        
        tabName = "dash1",
        
        imageOutput("coverPage")
        
      ),
      
      tabItem(
        
        tabName = "dash2",
        tabsetPanel(type = "tab",
                    tabPanel("Payment Methods & Membership", 
                             style = "margin-top: 25px;",
                             box(title = "Analysing Sales Patterns: Membership, Payment Methods And Gender", status = "primary", solidHeader = TRUE, plotOutput("side_by_side_chart"), width = NULL, style = "height: auto;")
                             
                    ),
                    tabPanel("Number of Products", 
                             style = "margin-top: 25px;",
                             box(title = "Total Number of Products Purchased by Gender", status = "primary", solidHeader = TRUE, plotOutput("Butterfly"), width = NULL, style = "height: auto;")
                             
                             
                    )
        )
                         
      ),
      
      
      
      tabItem(
        
        tabName = "dash3",
        tabsetPanel(type = "tab",
                    tabPanel("Total Sales by Branch", 
                             selectInput("branch", label = "Select Branch:",
                                         choices = c("A", "B", "C")),
                             box(title = "Total Sales by Product Type and Branch", status = "primary", solidHeader = TRUE, plotOutput("barplot"), style = "height: auto;"),
                             box(title = "Total Sales by Product Type and Branch", status = "primary", solidHeader = TRUE, plotOutput("combined_barplot"), style = "height: auto;")
                             
                             
                    ),
                    
                    tabPanel("Total Sales by Product Category",
                             style = "margin-top: 25px;",
                             box(title = "Total Sales by Product Type", status = "primary", solidHeader = TRUE, plotOutput("lolipop_sales"), width = NULL, style = "height: auto;")

                    )
        )
        
      ),
      
      tabItem(
        
        tabName = "dash4",
        tabsetPanel(type = "tab",
                    tabPanel("Gross Income by Branch", 
                             selectInput("branch", label = "Select Branch:",
                                         choices = c("A", "B", "C")),
                             box(title = "Gross Income by Branch", status = "primary", solidHeader = TRUE, plotOutput("boxplot"), style = "height: auto;"),
                             box(title = "Gross Income by Branch", status = "primary", solidHeader = TRUE, plotlyOutput("combined_boxplot"), style = "height: auto;")
                             
                             
                    ),
                    
                    tabPanel("Gross Income Distibution",
                             style = "margin-top: 25px;",
                             box(title = "Distribution of Gross Income", status = "primary", solidHeader = TRUE, plotOutput("histogram"), width = NULL, style = "height: auto;"),
                    ),
                    tabPanel("Gross Income Trend",
                             style = "margin-top: 25px;",
                             box(title = "Gross Income Trend by Month and Branch", status = "primary", solidHeader = TRUE, plotlyOutput("lineChart"), width = NULL, style = "height: auto;")
                    )
        )
        
        
      ),
      
      
      
      tabItem(
        
        tabName = "summ",
        h1("Summary"),
        style = "margin-top: 25px;",
        tabPanel("Data Table", div(DT::dataTableOutput("sumTable"), style = "font-size: 55%"))
        
        
      )
      
    )
  )
)

server <- function(input, output) {
  
  # Cover Page
  output$coverPage <- renderImage(
    
    list(
      src = "C:\\UMPSA_Y2S2\\BSD2223 DSP II\\DSPII_Project\\cover page.png", width = "100%", height = "auto"
    ),
    deleteFile = FALSE
    
  )
  
  # Adjust customer type categories
  sales$CustType <- factor(sales$CustType)
  sales$CustType[sales$CustType %in% c("Credit card Member", "Cash Member", "Ewallet Member")] <- "Member"
  sales$CustType[sales$CustType %in% c("Ewallet Normal", "Cash Normal", "Credit card Normal")] <- "Non-member"
  
  # Calculate total for each category
  totals <- sales %>%
    group_by(CustType, Payment, Gender) %>%
    summarise(Total = sum(TotalPrice))
  
  # Render side-by-side chart
  output$side_by_side_chart <- renderPlot({
    
    # Create side-by-side chart
    ggplot(sales, aes(x = Payment, fill = CustType)) +
      geom_bar(position = "dodge", stat = "summary", fun = "sum", aes(y = TotalPrice)) +
      geom_text(data = totals, aes(label = ifelse(CustType == "Non-member", "normal", round(Total)), y = Total, group = CustType), 
                position = position_dodge(width = 0.9), vjust = -0.5, size = 3) +
      facet_grid(. ~ Gender) +
      labs(#title = "Side-by-Side Chart",
        x = "Payment Method",
        y = "Total Amount ($)") +
      theme(panel.grid = element_blank(),
            panel.background = element_rect(fill = "white"),
            plot.background = element_rect(fill = "white"),
            legend.background = element_rect(fill = "white")) + 
      scale_fill_discrete(name = "Customer Type", labels = c("Member", "Non-member"))
  })

  output$lolipop_sales <- renderPlot({
    
    sales %>% 
      group_by(ProductType) %>%
      summarise(sum_TotalPrice = sum(TotalPrice)) %>%
      mutate(ProductType = fct_reorder(ProductType, sum_TotalPrice)) %>%
      ggplot(aes(ProductType, sum_TotalPrice, colour=ProductType)) + 
      geom_point(size=3)+
      geom_segment(aes(x = ProductType,
                       y = sum(sales$TotalPrice) / n_distinct(sales$ProductType),  # This is the mean of total sales across all product types
                       xend = ProductType,
                       yend = sum_TotalPrice),
                   colour = "grey")+
      geom_hline(yintercept = sum(sales$TotalPrice) / n_distinct(sales$ProductType),  # This is the mean of total sales across all product types
                 colour = "grey",
                 size = 1)+
      geom_text(aes(label = round(sum_TotalPrice, 0)), vjust = -0.8, size = 3, color = "black") +
      theme_bw()+
      theme(axis.text.x = element_text(angle = 90),
            panel.grid = element_blank()) + 
      labs(
        x = "Product Type",
        y = "Total Sales ($)")
    
  })
  
  
  
  product_colors <- c("Electronic accessories"="plum1", "Food and beverages"="bisque", "Home and lifestyle"="lightblue", 
                      "Fashion accessories"="pink", "Health and beauty"="palegreen", "Sports and travel"="thistle")
  
  
  
  output$Butterfly <- renderPlot({
    
    sales %>%
      group_by(Gender, ProductType) %>%
      summarise(count = n()) %>%
      mutate(ProductType = fct_reorder(ProductType, count, .desc = TRUE)) %>% # Reorder product categories based on counts
      ggplot(aes(x = ProductType, y = count, fill = Gender)) +
      geom_bar(data = . %>% filter(Gender == "Female"), stat = "identity", position = "identity", width = 0.5) +
      geom_bar(data = . %>% filter(Gender == "Male"), aes(y = -count), stat = "identity", position = "dodge", width = 0.5) +
      geom_text(data = . %>% filter(Gender == "Female"), aes(label = count), vjust = -0.5, hjust = -0.1) +
      geom_text(data = . %>% filter(Gender == "Male"), aes(label = count, y = -count), vjust = -0.5, hjust = 1.1) + 
      scale_fill_manual(values = c("Female" = "pink", "Male" = "lightblue")) +
      coord_flip() +
      labs(y = "Quantity", x = "Product Type") +
      theme_minimal()+
      theme(panel.grid = element_blank())
    
  })
  
  
  # barplot
  output$barplot <- renderPlot({
    
    branch_data <- subset(sales, Branch == input$branch)
    
    # Group the data by 'ProductType' and aggregate 'Price' for each group
    grouped_data <- branch_data %>%
      group_by(ProductType) %>%
      summarise(Price = sum(Price, na.rm = TRUE))
    
    # Create a bar plot 
    p <- ggplot(grouped_data, aes(x = ProductType, y = Price, fill = ProductType)) +
      geom_bar(stat = "identity") +
      geom_text(aes(label = round(Price)), vjust = -0.5, size = 3) +
      labs(title = paste("Total Sales for Branch", input$branch, "by Product Type"),
           x = "Product Type",
           y = "Total Sales ($)") +
      theme_minimal() +
      theme(legend.position = "none",
            panel.grid = element_blank()) +
      scale_fill_manual(values = product_colors) 
    
    print(p)
    
  })
  
  #combined_barplot
  output$combined_barplot <- renderPlot({
    grouped_data <- sales %>%
      group_by(Branch, ProductType) %>%
      summarise(Price = sum(Price, na.rm = TRUE)) %>%
      pivot_wider(names_from = ProductType, values_from = Price, values_fill = 0)
    
    branches <- grouped_data$Branch
    product_types <- colnames(grouped_data)[-1]
    
    max_product_types <- 5
    product_types_to_plot <- product_types[1:max_product_types]
    
    #bar_width <- 0.5
    
    x <- seq(1, length(branches))
    
    plot_data <- data.frame(x = rep(x, length(product_types_to_plot)),
                            y = unlist(grouped_data[product_types_to_plot]),
                            product_type = rep(product_types_to_plot, each = length(branches)),
                            branch = rep(branches, length(product_types_to_plot))
    )
    
    # Calculate middle position of each bar for the labels
    plot_data <- plot_data %>%
      group_by(branch, product_type) %>%
      mutate(y_mid = y / 2)
    
    p <- ggplot(plot_data, aes(x = x, y = y, fill = product_type)) +
      geom_bar(stat = "identity", width = 0.5, position = position_dodge(width = 0.6)) + 
      geom_text(aes(y = y_mid, label = product_type), vjust = 0.5, size = 3, angle = 90, hjust = 0.5, position = position_dodge(width = 0.6)) +
      geom_text(aes(label = round(y)), vjust = 0.5, size = 3, angle = 90, hjust = 1.2, position = position_dodge(width = 0.6), color = "black") +
      scale_x_continuous(breaks = x, labels = branches) +
      labs(#title = "Bar plot of Total Sales by Product Type and Branch",
        x = "Branch",
        y = "Total Sales ($)") + 
      theme_minimal() + 
      theme(legend.position = "none",
            panel.grid = element_blank()) + 
      scale_fill_manual(values = product_colors) 
    
    print(p)
  })
  
  
  output$boxplot <- renderPlot({
    branch_data <- subset(sales, Branch == input$branch)
    
    p <- ggplot(branch_data, aes(x = Branch, y = GIncome, fill = Branch)) +
      geom_boxplot() +
      labs(title = paste("Gross Income for Branch", input$branch),
           x = "Branch",
           y = "Gross Income ($)") +
      theme_minimal() +
      theme(legend.position = "none",
            panel.grid = element_blank()) +
      scale_fill_manual(values = c("A" = "violet", "B" = "skyblue", "C" = "salmon"))
    
    print(p)
    
  })
  
  
  output$combined_boxplot <- renderPlotly({
    
    # Create the ggplot object
    p <- ggplot(sales, aes(x = Branch, y = GIncome, fill = Branch)) +
      geom_boxplot() +
      labs(x = "Branch", y = "Gross Income ($)") +
      theme_minimal() +
      theme(legend.position = "none", panel.grid = element_blank()) +
      scale_fill_manual(values = c("violet", "skyblue", "salmon")) 
      
     
    # Convert ggplot to plotly
    p <- ggplotly(p, tooltip = "text")
    p <- layout(p, font = list(family = "Arial"))
    
    print(p)
    
    
    
  })
  
  
  
  selected_data <- reactive({
    sales[sales$Gender == input$gender, ]
  })
  
  output$histogram <- renderPlot({
    
    # Reset the margins to default after plotting
    par(mar = c(5, 4, 0, 2) + 0.1)    # Bottom, left, top, and right margins
    
    
    hist(sales$GIncome, freq = FALSE,
         main = "",
         xlab = "Gross Income ($)",
         ylab = "Density", # Changed to Density
         col = "goldenrod1",
         border = "goldenrod4",
         ylim = c(0, max(density(sales$GIncome)$y) * 1.2) # Adjust the range of y-axis
    )
    lines(density(sales$GIncome), col="red", lwd=1.5) # Changed to density
    
    
  })
  
 
  
  # Reactive expression for filtered data
  filtered_data <- reactive({
    if ("All" %in% input$cityFilter) {
      return(sales)
    } else {
      return(sales[sales$City %in% input$cityFilter, ])
    }
  })
  
  # Plotting line chart
  output$lineChart <- renderPlotly({
    
    filtered_data_copy <- sales %>%
      mutate(YearMonth = floor_date(Date, "month")) %>%
      group_by(City, YearMonth) %>%
      summarize(GIncome = sum(GIncome, na.rm = TRUE), .groups = 'drop') %>%
      ungroup()
    
    # Create tick values and labels for three months only
    first_month <- min(filtered_data_copy$YearMonth)
    tickvals <- seq(first_month, by = "1 month", length.out = 3)
    ticktext <- format(tickvals, "%b %Y")
    
    
    plot_ly(filtered_data_copy, x = ~YearMonth, y = ~GIncome, color = ~City, type = 'scatter', mode = 'lines+markers+text', text = ~paste(round(GIncome)), 
            textposition = 'top center') %>%
      layout(#title = "Gross Income Trend by Month and City",
             xaxis = list(title = "Month", tickvals = tickvals, ticktext = ticktext),
             yaxis = list(title = "Gross Income ($)"),
             showlegend = TRUE,
             margin = list(t = 20, b = 70, l = 100, r = 50),
             font = list(
               family = "Arial"
             )
        )
  })
  
  output$sumTable <- DT::renderDataTable({
    
    DT::datatable(sales, extensions = 'Buttons', options = list(
      dom = 'Bfrtip',
      buttons = c('copy', 'csv', 'excel', 'pdf', 'print')
    ))
    
  })
 
  
  
  
}

shinyApp(ui = ui, server = server)
