if ARGV.count < 3 || ARGV[2].length < 5
    puts "./usage height width characters"
  else
    height, width, chars, gates = ARGV[0].to_i, ARGV[1].to_i, ARGV[2], ARGV[3].to_i
    entry = rand(width - 4) + 2
    entry2 = rand(width - 4) + 2
    filename = "maze.txt" # Specify the filename where you want to save the maze.
  
    File.open(filename, "w") do |file|
      file.puts("#{height}x#{width}#{ARGV[2]}")
      height.times do |y|
        width.times do |x|
          if y == 0 && x == entry
            file.print chars[3].chr
          elsif y == height - 1 && x == entry2
            file.print chars[4].chr
          elsif y.between?(1, height - 2) && x.between?(1, width - 2) && rand(100) > 20
            file.print chars[1].chr
          else
            file.print chars[0].chr
          end
        end
        file.puts
      end
    end
  
    puts("Maze generated and saved to '#{filename}'.")
  end
  